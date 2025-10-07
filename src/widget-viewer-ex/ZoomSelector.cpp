#include "ZoomSelector.hpp"

#include <QtCore/QLatin1Char>
#include <QtCore/QLatin1String>
#include <QtCore/QString>
#include <QtWidgets/QLineEdit>


namespace widget_viewer {
ZoomSelector::ZoomSelector (QWidget* parent) : QComboBox{parent} {
    setEditable(true);

    addItem(QLatin1String("Fit Width"));
    addItem(QLatin1String("Fit Page"));
    addItem(QLatin1String("12%"));
    addItem(QLatin1String("25%"));
    addItem(QLatin1String("33%"));
    addItem(QLatin1String("50%"));
    addItem(QLatin1String("66%"));
    addItem(QLatin1String("75%"));
    addItem(QLatin1String("100%"));
    addItem(QLatin1String("125%"));
    addItem(QLatin1String("150%"));
    addItem(QLatin1String("200%"));
    addItem(QLatin1String("400%"));

    connect(
        this, &QComboBox::currentTextChanged,
        this, &ZoomSelector::on_current_text_changed
    );

    connect(
        lineEdit(), &QLineEdit::editingFinished,
        this, [this] () { on_current_text_changed(lineEdit()->text()); }
    );
}

void ZoomSelector::set_zoom_factor (qreal zoom_factor) {
    setCurrentText(
        QString::number(qRound(zoom_factor * 100)) + QLatin1String("%")
    );
}

void ZoomSelector::reset () {
    setCurrentIndex(8);  // 100%
}

void ZoomSelector::on_current_text_changed (QString const& text) {
    if (text == QLatin1String("Fit Width")) {
        emit zoom_mode_changed(QPdfView::ZoomMode::FitToWidth);
    } else if (text == QLatin1String("Fit Page")) {
        emit zoom_mode_changed(QPdfView::ZoomMode::FitInView);
    } else {
        qreal factor = 1.0;

        QString without_percent{text};
        without_percent.remove(QLatin1Char{'%'});

        bool ok = false;
        int const zoom_level = without_percent.toInt(&ok);
        if (ok) {
            factor = zoom_level / 100.0;
        }

        emit zoom_mode_changed(QPdfView::ZoomMode::Custom);
        emit zoom_factor_changed(factor);
    }
}
}  // namespace widget_viewer
