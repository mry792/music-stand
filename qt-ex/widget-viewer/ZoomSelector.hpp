#pragma once

#include <QtCore/QObject>
#include <QtCore/QtGlobal>
#include <QtPdfWidgets/QPdfView>
#include <QtWidgets/QComboBox>

class QString;
class QWidget;


namespace widget_viewer {
class ZoomSelector : public QComboBox {
    Q_OBJECT

  public:
    explicit ZoomSelector (QWidget* parent = nullptr);

  public slots:
    void set_zoom_factor (qreal zoom_factor);

    void reset ();

  signals:
    void zoom_mode_changed (QPdfView::ZoomMode zoom_mode);
    void zoom_factor_changed (qreal zoom_factor);

  private slots:
    void on_current_text_changed (QString const& text);
};
}  // namespace widget_viewer
