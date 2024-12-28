pragma Singleton
import QtQuick
import QtQuick.Controls.Universal

import QFRCScouter

QtObject {
    readonly property int width: 1920
    readonly property int height: 1080

    property color accent: config.object.qmlAccent
    property color button: config.object.button
    property color buttonPressed: config.object.buttonPressed
    property color buttonText: config.object.buttonText

    readonly property color bg: config.object.backgroundColor
    readonly property color text: config.object.textColor
}
