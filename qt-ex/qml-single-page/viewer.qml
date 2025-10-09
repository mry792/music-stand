import QtQuick.Controls

ApplicationWindow {
    id: root
    width: 800
    height: 1024
    color: "lightgrey"
    // title: document.title
    visible: true
    required property url source  // for main.cpp
    property real scaleStep: Math.sqrt(2)
}
