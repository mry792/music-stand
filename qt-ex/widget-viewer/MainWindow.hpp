#pragma once

#include <memory>

#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMainWindow>

class QFileDialog;
class QLineEdit;
class QModelIndex;
class QPdfDocument;
class QPdfPageSelector;
class QPdfSearchModel;
class QUrl;
class QWidget;

namespace Ui            { class MainWindow; }
namespace widget_viewer { class ZoomSelector; }

Q_DECLARE_LOGGING_CATEGORY(lcExample)

namespace widget_viewer {
class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow (QWidget* parent = nullptr);
    ~MainWindow ();

  public slots:
    void open (QUrl const& document_location);

  private slots:
    void bookmark_selected (QModelIndex const& index);
    void page_selected (int page);
    void search_result_selected (QModelIndex const& current, QModelIndex const& previous);

    // action handlers (need to be named exactly as they correspond to *.ui actions)
    void on_actionOpen_triggered ();
    void on_actionQuit_triggered ();
    void on_actionAbout_triggered ();
    void on_actionAbout_Qt_triggered ();
    void on_actionZoom_In_triggered ();
    void on_actionZoom_Out_triggered ();
    void on_actionPrevious_Page_triggered ();
    void on_actionNext_Page_triggered ();
    void on_thumbnailsView_activated (QModelIndex const& index);
    void on_actionContinuous_triggered ();
    void on_actionBack_triggered ();
    void on_actionForward_triggered ();
    void on_actionFindNext_triggered ();
    void on_actionFindPrevious_triggered ();

  private:
    std::unique_ptr<Ui::MainWindow> ui_;

    ZoomSelector* zoom_selector_;
    QPdfPageSelector* page_selector_;
    QPdfSearchModel* search_model_;
    QLineEdit* search_field_;
    QFileDialog* file_dialog_ = nullptr;

    QPdfDocument* document_;
};
}  // namespace widget_viewer
