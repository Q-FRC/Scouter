import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import QFRCScouter

ColumnLayout {
    id: scaleItem

    spacing: 5

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
        font.pixelSize: 25
        text: title
    }

    RowLayout {
        Layout.fillWidth: true
        uniformCellSizes: true
        spacing: 2

        Repeater {
            id: rep
            model: ["Awful", "Bad", "N/A", "Fine", "Good", "Great", "Elite"]

            ScaleCheckbox {
                // Layout.fillWidth: true
                Layout.preferredWidth: 100

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
        font.pixelSize: 16
        wrapMode: Text.WordWrap
        text: desc
        color: Constants.text

        Layout.leftMargin: 15
        Layout.rightMargin: 50

        Layout.topMargin: 50
    }
}
