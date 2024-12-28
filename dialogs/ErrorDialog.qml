import QtQuick
import QtQuick.Controls

import QFRCScouter

AnimatedDialog {
    id: errors
    required property string text

    width: 350
    height: 450

    anchors.centerIn: Overlay.overlay

    Text {
        font.pixelSize: 20
        color: Constants.text
        text: errors.text

        wrapMode: Text.WordWrap
        anchors.fill: parent
    }

    standardButtons: Dialog.Ok
}
