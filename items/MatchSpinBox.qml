import QtQuick
import QtQuick.Controls

import QFRCScouter

SpinBox {
    id: spin
    required property string text
    required property string textColor
    required property string buttonColor
    required property string type
    required property int min
    required property int max
    required property int idx
    required property int columns
    required property int multiplier

    property string label: text

    /** what property to bind to */
    property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    font.pixelSize: 24 * Constants.scalar

    from: min
    to: max

    editable: false

    value: 0
    onValueModified: {
        bindTarget[bindedProperty][idx] = value * multiplier
    }

    contentItem: TextInput {
        text: parent.textFromValue(parent.value, parent.locale)

        font: parent.font
        color: Constants.text
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        width: parent.width / 3
        readOnly: !spin.editable

        inputMethodHints: Qt.ImhFormattedNumbersOnly

        onEditingFinished: spin.value = parseInt(text.replace(/,/g, ""))
    }

    up.indicator: Rectangle {
        x: parent.width * 2 / 3
        height: parent.height
        width: parent.width / 3
        radius: 5

        color: buttonColor

        Text {
            text: "+"
            font.pixelSize: spin.font.pixelSize * 1.5
            color: textColor
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

        color: buttonColor

        Text {
            text: "-"
            font.pixelSize: spin.font.pixelSize * 1.5
            color: textColor
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Rectangle {
        color: Constants.bg
        border.color: buttonColor
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
