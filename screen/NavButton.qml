import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QFRCScouter

import QtQuick.Controls.Universal

Button {
    Layout.preferredWidth: parent.width / 3
    Layout.fillHeight: true
    
    font.pixelSize: 30
    
    background: Rectangle {
        radius: 5
        
        color: parent.pressed ? Constants.buttonPressed : Constants.button
    }
    
    Universal.foreground: Constants.buttonText
}
