
#include <cstdlib>

#include <QtCore/QCommandLineParser>
#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QtConfig>
#include <QtCore/QUrl>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

int main (int argc, char* argv[]) {
    using Qt::Literals::StringLiterals::operator""_s;

    QCoreApplication::setApplicationName("Qt Quick PDF Viewer Example");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QGuiApplication app{argc, argv};

    QCommandLineParser parser{};
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    QQmlApplicationEngine engine{};

    QUrl to_load{"qrc:/singlepage/resources/test.pdf"};
    if (not parser.positionalArguments().isEmpty()) {
        to_load = QUrl::fromLocalFile(parser.positionalArguments().constFirst());
    }
    engine.setInitialProperties({{"source", to_load}});

    engine.load(QUrl{u"qrc:/qt/qml/singlepage/viewer.qml"_s});
    if (engine.rootObjects().isEmpty()) {
        return EXIT_FAILURE;
    }

    return app.exec();
}
