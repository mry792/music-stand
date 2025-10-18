
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <QtCore/QtVersion>
#include <QtQml/QQmlApplicationEngine>
#include <QtCore/QString>

#include "PdfApplication.hpp"

int main (int argc, char* argv[]) {
    using Qt::Literals::StringLiterals::operator ""_s;

    QCoreApplication::setApplicationName("Qt Quick Multi-page PDF Viewer Example");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    qml_multipage::PdfApplication app{argc, argv};

    QQmlApplicationEngine engine{};
    engine.load(QUrl{u"qrc:/qt/qml/multipage/viewer.qml"_s});
    auto* root = engine.rootObjects().constFirst();
    app.file_opener(root);

    if (app.arguments().count() > 1) {
        // Alternatively, use QUrl::fromLocalFile() - network loading is not supported yet.
        auto to_load = QUrl::fromUserInput(
            app.arguments().at(1),
            QDir::currentPath(),
            QUrl::AssumeLocalFile
        );
        root->setProperty("source", to_load);
    } else {
        root->setProperty("source", u"qrc:/multipage/resources/test.pdf"_s);
    }

    return app.exec();
}
