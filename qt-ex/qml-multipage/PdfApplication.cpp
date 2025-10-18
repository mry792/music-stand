#include "PdfApplication.hpp"

#include <QtCore/QEvent>
#include <QtGui/QFileOpenEvent>

namespace qml_multipage {
// override
bool PdfApplication::event (QEvent* e) {
    assert(e);

    if (e->type() == QEvent::FileOpen) {
        auto& event = static_cast<QFileOpenEvent&>(*e);
        file_opener_->setProperty("source", event.url());
    }

    return QGuiApplication::event(e);
}
} // namespace qml_multipage
