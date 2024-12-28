import QtQuick

import QFRCScouter

Rectangle {
    required property string title

    color: Constants.accent
    width: parent.width
    height: 50 * Constants.scalar
    radius: 20

    anchors {
        top: parent.top
        left: parent.left
        right: parent.right
    }

    Text {
        anchors {
            fill: parent
        }

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: Constants.buttonText

        font.pixelSize: 30 * Constants.scalar
        font.bold: true

        text: parent.title
    }
}
