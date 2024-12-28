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
        font.pixelSize: 25
        color: Constants.text

        anchors.centerIn: parent

        horizontalAlignment: Text.AlignHCenter
    }

    Button {
        height: 80
        width: 500

        font.pixelSize: 30

        background: Rectangle {
            radius: 5

            color: parent.pressed ? Constants.buttonPressed : Constants.button
        }

        anchors {
            horizontalCenter: txt.horizontalCenter
            top: txt.bottom

            topMargin: 30
        }

        Universal.foreground: Constants.buttonText

        text: "Back to QR Code"
        onClicked: backToCode()

        visible: backAvailable
    }
}
