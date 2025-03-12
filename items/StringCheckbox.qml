import QtQuick 2.15
import QtQuick.Controls 2.15

import QFRCScouter

Item {
    required property string text
    required property int idx
    required property int parentIdx

    property alias control: control

    /** what property to bind to */
    required property string bindedProperty

    /** the target to bind the property to */
    required property var bindTarget

    CheckBox {
        id: control
        font.pixelSize: 18 * Constants.scalar

        property bool ready: false

        indicator.implicitHeight: 35 * Constants.scalar
        indicator.implicitWidth: 35 * Constants.scalar

        Component.onCompleted: ready = true
        onCheckedChanged: if (checked && ready) {
                              bindTarget[bindedProperty][parentIdx] = idx
                          }
    }

    Text {
        font.pixelSize: 18 * Constants.scalar
        text: parent.text
        color: Constants.text
        verticalAlignment: Text.AlignVCenter

        anchors {
            bottom: control.top
            horizontalCenter: control.horizontalCenter
        }
    }
}
