import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import QFRCScouter

ColumnLayout {
    id: stringItem

    spacing: 25

    function clear() {
        rep.itemAt(0).control.checked = true
    }

    required property string text
    required property list<string> choices
    required property int idx
    required property int columns

    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    ButtonGroup {
        id: group
        exclusive: true
    }

    Text {
        Layout.fillWidth: true

        color: Constants.text
        font.pixelSize: 20 * Constants.scalar
        text: stringItem.text
    }

    RowLayout {
        Layout.fillWidth: true
        spacing: 2

        Repeater {
            id: rep
            model: choices

            StringCheckbox {
                Layout.preferredWidth: 100 * Constants.scalar * (Constants.isVertical ? 0.8 : 1.0)

                required property string modelData
                required property int index

                bindTarget: stringItem.bindTarget
                bindedProperty: stringItem.bindedProperty

                text: modelData
                idx: index
                parentIdx: stringItem.idx

                control.ButtonGroup.group: group

                Component.onCompleted: if (idx === 0)
                                           control.checked = true
            }
        }
    }
}
