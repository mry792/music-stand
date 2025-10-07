
#include "MainWindow.hpp"

#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCoreApplication>
#include <QtCore/QUrl>
#include <QtWidgets/QApplication>


int main (int argc, char* argv[]) {
    QCoreApplication::setApplicationName("widget viewer");
    QCoreApplication::setOrganizationName("Qt PDF demos");

    QApplication app{argc, argv};

    QCommandLineParser parser{};
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    widget_viewer::MainWindow window{};
    window.show();
    if (not parser.positionalArguments().isEmpty()) {
        auto const file_path = parser.positionalArguments().constFirst();
        auto const document_location = QUrl::fromLocalFile(file_path);
        window.open(document_location);
    }

    return app.exec();
}
