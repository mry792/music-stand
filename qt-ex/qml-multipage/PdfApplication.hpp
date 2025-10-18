#pragma once

#include <QtGui/QGuiApplication>

class QEvent;
class QObject;

namespace qml_multipage {
class PdfApplication : public QGuiApplication {
  public:
    using QGuiApplication::QGuiApplication;

    void file_opener (QObject* opener) {
        file_opener_ = opener;
    }

  private:
    QObject* file_opener_ = nullptr;

    bool event (QEvent* e) override;
};
} // namespace qml_multipage
