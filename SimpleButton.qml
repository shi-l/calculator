import QtQuick
import QtQuick.Layouts
Rectangle {
    signal clicked
    property alias text: text.text
    border.width: 2
    border.color: "black"

    height: 35
    width: parent.width / 5
    radius: 8


    Text {
        id: text
        anchors.centerIn: parent

        font.pixelSize: 16
        color: "#1b1c1d"
        font.family: "Open Sans Regular"
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}

