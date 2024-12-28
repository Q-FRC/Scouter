import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import QFRCScouter

ColumnLayout {
    id: scaleItem

    spacing: 25

    function clear() {
        rep.itemAt(2).control.checked = true
    }

    required property string title
    required property string desc
    required property int idx

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
        font.pixelSize: 25 * Constants.scalar
        text: title
    }

    RowLayout {
        Layout.fillWidth: true
        spacing: 2

        Repeater {
            id: rep
            model: ["Awful", "Bad", "N/A", "Fine", "Good", "Great", "Elite"]

            ScaleCheckbox {
                Layout.preferredWidth: 70 * Constants.scalar * (Constants.isVertical ? 0.8 : 1.0)

                required property string modelData
                required property int index

                text: modelData
                type: "bool"
                idx: index - 2
                scaleIdx: scaleItem.idx

                bindedProperty: scaleItem.bindedProperty
                bindTarget: scaleItem.bindTarget

                control.ButtonGroup.group: group

                Component.onCompleted: if (idx === 0) control.checked = true
            }
        }
    }

    Text {
        font.pixelSize: 16 * Constants.scalar
        wrapMode: Text.WordWrap
        text: desc
        color: Constants.text

        Layout.leftMargin: 15 * Constants.scalar
        Layout.rightMargin: 50 * Constants.scalar

        Layout.topMargin: 50 * Constants.scalar
    }
}
