import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import QFRCScouter

import QtQuick.Controls.Universal

Button {
    Layout.preferredWidth: parent.width / 3
    Layout.fillHeight: true
    
    font.pixelSize: 30 * Constants.scalar
    
    background: Rectangle {
        radius: 5
        
        color: parent.pressed ? Constants.buttonPressed : Constants.button
    }
    
    Universal.foreground: Constants.buttonText

    // if this isn't done, then the previously selected textbox will never lose focus
    onClicked: focus = true
}
