import QtQuick
import QtQuick.Controls

import QFRCScouter

TextField {
    required property string label

    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    id: textField
    font.pixelSize: 24 * Constants.scalar

    color: Constants.text
    text: bindTarget[bindedProperty]

    onTextEdited: bindTarget[bindedProperty] = text
    onEditingFinished: bindTarget[bindedProperty] = text

    background: Rectangle {
        color: Constants.bg
        width: parent.width
        border.color: Constants.text
        border.width: 2
        radius: 5
    }

    Text {
        id: floatingLabel
        text: label
        color: Constants.text

        font.pixelSize: 20 * Constants.scalar

        anchors {
            left: textField.left
            bottom: textField.top

            bottomMargin: -2
            leftMargin: 10
        }
    }
}
