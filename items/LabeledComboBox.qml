import QtQuick
import QtQuick.Controls

import QFRCScouter

ComboBox {
    required property string label

    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    /** choices for the combobox */
    required property var choices

    id: combo
    model: choices
    font.pixelSize: 24 * Constants.scalar

    height: 50 * Constants.scalar

    currentIndex: 0
    onCurrentTextChanged: bindTarget[bindedProperty] = currentText

    delegate: ItemDelegate {
        id: delegate

        width: combo.width
        contentItem: Text {
            text: modelData
            color: modelData.includes("Red") ? "red" : "blue"

            font.pixelSize: 24 * Constants.scalar
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: combo.highlightedIndex === index
    }

    Text {
        id: floatingLabel
        text: label
        color: Constants.text

        font.pixelSize: 20 * Constants.scalar

        anchors {
            left: parent.left
            bottom: parent.top

            bottomMargin: -2
            leftMargin: 10
        }
    }
}
