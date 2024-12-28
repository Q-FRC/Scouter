import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCScouter

Item {
    required property string text
    required property string type
    required property int idx

    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    property alias control: control

    CheckBox {
        id: control
        font.pixelSize: 24 * Constants.scalar

        indicator.implicitHeight: 40 * Constants.scalar
        indicator.implicitWidth: 40 * Constants.scalar

        onCheckedChanged: bindTarget[bindedProperty][idx] = checked ? 1 : 0

        text: parent.text

        contentItem: Text {
            text: control.text
            font: control.font
            opacity: enabled ? 1.0 : 0.3
            color: Constants.text
            verticalAlignment: Text.AlignVCenter
            leftPadding: control.indicator.width + control.spacing
        }
    }
}
