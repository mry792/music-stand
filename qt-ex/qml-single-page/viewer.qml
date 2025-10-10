import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Pdf

ApplicationWindow {
    id: root
    width: 800
    height: 1024
    color: "lightgrey"
    title: document.title
    visible: true
    required property url source  // for main.cpp
    property real scaleStep: Math.sqrt(2)

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: 6

            ToolButton {
                action: Action {
                    shortcut: StandardKey.Open
                    icon.source: "qrc:/qt/qml/singlepage/resources/document-open.svg"
                    onTriggered: fileDialog.open()
                }
            }
        }
    }

    PdfScrollablePageView {
        id: view
        anchors.fill: parent
        anchors.leftMargin: searchDrawer.position * searchDrawer.width
        document: PdfDocument {
            id: document
            source: Qt.resolvedUrl(root.source)
            onPasswordRequired: passwordDialog.open()
        }
    }

    FileDialog {
        id: fileDialog
        title: "Open a PDF file"
        nameFilters: [ "PDF files (*.pdf)" ]
        onAccepted: document.source = selectedFile
    }
}
