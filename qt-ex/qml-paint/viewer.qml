import QtQuick
import QtQuick.Controls
import QtQuick.Shapes

ApplicationWindow {
    id: root
    width: 800
    height: 600
    color: "lightgrey"
    visible: true

    Row {
        id: colorTools
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 8
        }
        property color paintColor: "#33B5E5"
        spacing: 4
        Repeater {
            model: ["#33B5E5", "#99CC00", "#FFBB33", "#FF4444"]
            ColorSquare {
                color: modelData
                active: parent.paintColor === color
                onClicked: {
                    parent.paintColor = color
                }
            }
        }
    }

    Canvas {
        id: canvas
        anchors {
            left: parent.left
            right: parent.right
            top: colorTools.bottom
            bottom: parent.bottom
            margins: 8
        }
        property real last_x
        property real last_y
        property color color: colorTools.paintColor

        onPaint: {
            var ctx = getContext('2d')
            ctx.lineWidth = 1.5
            ctx.strokeStyle = canvas.color
            ctx.beginPath()
            ctx.moveTo(last_x, last_y)
            last_x = area.mouseX
            last_y = area.mouseY
            ctx.lineTo(last_x, last_y)
            ctx.stroke()
        }

        MouseArea {
            id: area
            anchors.fill: parent
            onPressed: {
                canvas.last_x = mouseX
                canvas.last_y = mouseY
            }
            onPositionChanged: {
                canvas.requestPaint()
            }
        }
    }
}
