import QtQuick

Rectangle {
    width: 50
    height: 50
    signal clicked()
    property bool active: false

    border.color: "darkgrey"
    border.width: active ? 4 : 0

    MouseArea {
        anchors.fill: parent
        onClicked: {
            parent.clicked()
        }
    }
}
