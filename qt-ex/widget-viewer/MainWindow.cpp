#include "MainWindow.hpp"

#include <QtCore/QModelIndex>
#include <QtCore/QStandardPaths>
#include <QtCore/QStringLiteral>
#include <QtCore/QtMath>
#include <QtCore/QtPreprocessorSupport>
#include <QtGui/QShortcut>
#include <QtPdf/QPdfBookmarkModel>
#include <QtPdf/QPdfDocument>
#include <QtPdf/QPdfPageNavigator>
#include <QtPdf/QPdfSearchModel>
#include <QtPdfWidgets/QPdfPageSelector>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QSpinBox>
// #include <???/QShortcut>

#include "SearchResultDelegate.hpp"
#include "ZoomSelector.hpp"
#include "ui_MainWindow.h"


qreal const zoom_multiplier = qSqrt(2.0);
Q_LOGGING_CATEGORY(lcExample, "qt.examples.pdfviewer")


namespace widget_viewer {
MainWindow::MainWindow (QWidget* parent)
      : QMainWindow{parent},
        ui_{std::make_unique<Ui::MainWindow>()},
        zoom_selector_{new ZoomSelector(this)},
        page_selector_{new QPdfPageSelector(this)},
        search_model_{new QPdfSearchModel(this)},
        search_field_{new QLineEdit(this)},
        document_{new QPdfDocument(this)}
{
    ui_->setupUi(this);

    zoom_selector_->setMaximumWidth(150);
    ui_->mainToolBar->insertWidget(ui_->actionZoom_In, zoom_selector_);

    ui_->mainToolBar->insertWidget(ui_->actionForward, page_selector_);
    connect(page_selector_, &QPdfPageSelector::currentPageChanged, this, &MainWindow::page_selected);
    page_selector_->setDocument(document_);

    auto nav = ui_->pdfView->pageNavigator();
    connect(nav, &QPdfPageNavigator::currentPageChanged, page_selector_, &QPdfPageSelector::setCurrentPage);
    connect(nav, &QPdfPageNavigator::backAvailableChanged, ui_->actionBack, &QAction::setEnabled);
    connect(nav, &QPdfPageNavigator::forwardAvailableChanged, ui_->actionForward, &QAction::setEnabled);

    connect(zoom_selector_, &ZoomSelector::zoom_mode_changed, ui_->pdfView, &QPdfView::setZoomMode);
    connect(zoom_selector_, &ZoomSelector::zoom_factor_changed, ui_->pdfView, &QPdfView::setZoomFactor);
    zoom_selector_->reset();

    QPdfBookmarkModel* bookmark_model = new QPdfBookmarkModel(this);
    bookmark_model->setDocument(document_);
    ui_->bookmarkView->setModel(bookmark_model);
    connect(ui_->bookmarkView, &QAbstractItemView::activated, this, &MainWindow::bookmark_selected);

    ui_->thumbnailsView->setModel(document_->pageModel());

    search_model_->setDocument(document_);
    ui_->pdfView->setSearchModel(search_model_);
    ui_->searchToolBar->insertWidget(ui_->actionFindPrevious, search_field_);
    connect(
        new QShortcut(QKeySequence::Find, this), &QShortcut::activated,
        this, [this] () { search_field_->setFocus(Qt::ShortcutFocusReason); }
    );

    search_field_->setPlaceholderText(tr("Find in document"));
    search_field_->setMaximumWidth(400);
    connect(
        search_field_, &QLineEdit::textEdited,
        this, [this] (QString const& text) {
            search_model_->setSearchString(text);
            ui_->tabWidget->setCurrentWidget(ui_->searchResultsTab);
        }
    );

    ui_->searchResultsView->setModel(search_model_);
    ui_->searchResultsView->setItemDelegate(new SearchResultDelegate(this));
    connect(
        ui_->searchResultsView->selectionModel(), &QItemSelectionModel::currentChanged,
        this, &MainWindow::search_result_selected
    );

    ui_->pdfView->setDocument(document_);

    connect(
        ui_->pdfView, &QPdfView::zoomFactorChanged,
        zoom_selector_, &ZoomSelector::set_zoom_factor
    );
}

MainWindow::~MainWindow () = default;

void MainWindow::open (QUrl const& document_location) {
    if (document_location.isLocalFile()) {
        document_->load(document_location.toLocalFile());

        // auto const document_title = document_->metaData(QPdfDocument::MetaDataField::Title).toString();
        // setWindowTitle(document_location.isEmpty() ? QStringLiteral("PDF Viewer") : document_title);

        page_selected(0);
        // page_selector_->setMaximum(document_->pageCount() - 1);
    } else {
        QString const message = tr("%1 is not a valid local file").arg(document_location.toString());
        qCDebug(lcExample).noquote() << message;
        QMessageBox::critical(this, tr("Failed to open"), message);
    }

    qCDebug(lcExample) << document_location;
}

void MainWindow::bookmark_selected (QModelIndex const& index) {
    if (not index.isValid()) {
        return;
    }

    int const page = index.data(static_cast<int>(QPdfBookmarkModel::Role::Page)).toInt();
    qreal const zoom_level = index.data(static_cast<int>(QPdfBookmarkModel::Role::Level)).toReal();
    ui_->pdfView->pageNavigator()->jump(page, {}, zoom_level);
}

void MainWindow::page_selected (int page) {
    using namespace Qt::StringLiterals;

    auto nav = ui_->pdfView->pageNavigator();
    nav->jump(page, {}, nav->currentZoom());

    auto const document_title = document_->metaData(QPdfDocument::MetaDataField::Title).toString();
    setWindowTitle(not document_title.isEmpty() ? document_title : QStringLiteral("PDF Viewer"));
    setWindowTitle(tr("%1: page %2 (%3 of %4)").arg(
        document_title.isEmpty() ? u"PDF Viewer"_s : document_title,
        page_selector_->currentPageLabel(),
        QString::number(page + 1),
        QString::number(document_->pageCount())
    ));
}

void MainWindow::search_result_selected (QModelIndex const& current, QModelIndex const& previous) {
    Q_UNUSED(previous);
    if (not current.isValid()) {
        return;
    }

    int const page = current.data(static_cast<int>(QPdfSearchModel::Role::Page)).toInt();
    QPointF const location = current.data(static_cast<int>(QPdfSearchModel::Role::Location)).toPointF();
    ui_->pdfView->pageNavigator()->jump(page, location);
    ui_->pdfView->setCurrentSearchResultIndex(current.row());
}

//----
// action handlers

void MainWindow::on_actionOpen_triggered () {
    if (file_dialog_ == nullptr) {
        file_dialog_ = new QFileDialog(
            this,
            tr("Choose a PDF"),
            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
        );
        file_dialog_->setAcceptMode(QFileDialog::AcceptOpen);
        file_dialog_->setMimeTypeFilters({"application/pdf"});
    }

    if (file_dialog_->exec() == QDialog::Accepted) {
        QUrl const to_open = file_dialog_->selectedUrls().constFirst();
        if (to_open.isValid()) {
            open(to_open);
        }
    }
}

void MainWindow::on_actionQuit_triggered () {
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered () {
    QMessageBox::about(this, tr("About PdfViewer"), tr("An example using QPdfDocument"));
}

void MainWindow::on_actionAbout_Qt_triggered () {
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionZoom_In_triggered () {
    ui_->pdfView->setZoomFactor(ui_->pdfView->zoomFactor() * zoom_multiplier);
}

void MainWindow::on_actionZoom_Out_triggered () {
    ui_->pdfView->setZoomFactor(ui_->pdfView->zoomFactor() / zoom_multiplier);
}

void MainWindow::on_actionPrevious_Page_triggered () {
    auto nav = ui_->pdfView->pageNavigator();
    nav->jump(nav->currentPage() - 1, {}, nav->currentZoom());
}

void MainWindow::on_actionNext_Page_triggered () {
    auto nav = ui_->pdfView->pageNavigator();
    nav->jump(nav->currentPage() + 1, {}, nav->currentZoom());
}

void MainWindow::on_thumbnailsView_activated (QModelIndex const& index) {
    auto nav = ui_->pdfView->pageNavigator();
    nav->jump(index.row(), {}, nav->currentZoom());
}

void MainWindow::on_actionContinuous_triggered () {
    ui_->pdfView->setPageMode(
        ui_->actionContinuous->isChecked() ?
        QPdfView::PageMode::MultiPage :
        QPdfView::PageMode::SinglePage
    );
}

void MainWindow::on_actionBack_triggered () {
    ui_->pdfView->pageNavigator()->back();
}

void MainWindow::on_actionForward_triggered () {
    ui_->pdfView->pageNavigator()->forward();
}

void MainWindow::on_actionFindNext_triggered () {
    int next = ui_->searchResultsView->currentIndex().row() + 1;
    if (next >= search_model_->rowCount({})) {
        next = 0;
    }
    ui_->searchResultsView->setCurrentIndex(search_model_->index(next));
}

void MainWindow::on_actionFindPrevious_triggered () {
    int prev = ui_->searchResultsView->currentIndex().row() - 1;
    if (prev < 0) {
        prev = search_model_->rowCount({}) - 1;
    }
    ui_->searchResultsView->setCurrentIndex(search_model_->index(prev));
}
}  // namespace widget_viewer
