import QtQuick
import QtQuick.Controls

import QFRCScouter

SpinBox {
    id: spin
    required property string label

    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    font.pixelSize: 24 * Constants.scalar

    from: 0
    to: 1E9

    editable: true

    value: bindTarget[bindedProperty]
    onValueChanged: {
        bindTarget[bindedProperty] = value
    }

    contentItem: TextInput {
        text: parent.value

        font: parent.font
        color: Constants.text
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        width: parent.width / 3

        inputMethodHints: Qt.ImhFormattedNumbersOnly

        onTextEdited: spin.value = parseInt(text)
        onEditingFinished: spin.value = parseInt(text)
    }

    up.indicator: Rectangle {
        x: parent.width * 2 / 3
        height: parent.height
        width: parent.width / 3
        radius: 5

        color: spin.up.pressed ? Constants.buttonPressed : Constants.button

        Text {
            text: "+"
            font.pixelSize: spin.font.pixelSize * 2
            color: Constants.buttonText
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    down.indicator: Rectangle {
        x: 0
        height: parent.height
        width: parent.width / 3
        radius: 5

        color: spin.down.pressed ? Constants.buttonPressed : Constants.button

        Text {
            text: "-"
            font.pixelSize: spin.font.pixelSize * 2
            color: Constants.buttonText
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Rectangle {
        color: Constants.bg
        border.color: Constants.accent
        border.width: 2
        radius: 5
    }

    Text {
        id: floatingLabel
        text: label
        color: Constants.text

        font.pixelSize: 20 * Constants.scalar

        anchors {
            left: spin.left
            bottom: spin.top

            bottomMargin: -2
            leftMargin: 10
        }
    }
}
