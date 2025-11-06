
#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QtVersion>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

int main (int argc, char* argv[]) {
    using Qt::Literals::StringLiterals::operator ""_s;

    QCoreApplication::setApplicationName("Qt Quick Paint demo");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QGuiApplication app{argc, argv};

    QQmlApplicationEngine engine{};
    engine.load(QUrl{u"qrc:/qt/qml/paint/viewer.qml"_s});

    return app.exec();
}
