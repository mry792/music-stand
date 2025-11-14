#include "Application.hpp"

#include <QtCore/QString>
#include <QtCore/QUrl>


namespace music_stand {
Application::Application (int argc, char* argv[])
      : QGuiApplication{argc, argv} {
    using Qt::Literals::StringLiterals::operator ""_s;

    setApplicationName("Music Stand");
    setOrganizationName("M. Emery Goss");
    setApplicationVersion("0.0.0");

    engine_.load(QUrl{u"qrc:/qt/qml/music-stand/application.qml"_s});
}
}  // namespace music_stand
