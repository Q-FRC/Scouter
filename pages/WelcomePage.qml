import QtQuick
import QtQuick.Controls

import QFRCScouter

Rectangle {
    signal backToCode

    property bool backAvailable: false

    color: Constants.bg

    TitleBanner {
        title: "QFRCScouter"
    }

    Text {
        id: txt
        text: config.object.welcome

        wrapMode: Text.WordWrap
        font.pixelSize: 25 * Constants.scalar
        color: Constants.text

        anchors.centerIn: parent

        horizontalAlignment: Text.AlignHCenter

        width: parent.width * 0.8
    }

    Button {
        height: 80 * Constants.scalar
        width: 500 * Constants.scalar

        font.pixelSize: 30 * Constants.scalar

        background: Rectangle {
            radius: 5

            color: parent.pressed ? Constants.buttonPressed : Constants.button
        }

        anchors {
            horizontalCenter: txt.horizontalCenter
            top: txt.bottom

            topMargin: 30 * Constants.scalar
        }

        Universal.foreground: Constants.buttonText

        text: "Back to QR Code"
        onClicked: backToCode()

        visible: backAvailable
    }
}
