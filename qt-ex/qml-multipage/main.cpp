
// #include <filesystem>  // DEBUG
#include <iostream>  // DEBUG

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <QtCore/QtVersion>
#include <QtQml/QQmlApplicationEngine>
#include <QtCore/QString>

#include "PdfApplication.hpp"

// DEBUG
void print_contents (QDir const dir) {
    std::cerr << "D " << dir.absolutePath().toStdString() << "\n";
    auto const entries = dir.entryInfoList();
    /*
    std::cerr
        << "entry: " << dir.absolutePath().toStdString()
        << " has " << dir.count() << " entries:\n"
        ;
    */
    for (QFileInfo const& finfo : entries) {
        // std::cerr << path.toStdString() << "\n";
        if (finfo.isDir()) {
            print_contents(finfo.absoluteFilePath());
        } else {
            std::cerr << "F " << finfo.absoluteFilePath().toStdString() << "\n";
        }
    }
}

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

    // DEBUG
    // print_contents(QDir{":/"});

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
