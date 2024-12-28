import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import QFRCScouter

import QtQuick.Controls.Universal

ApplicationWindow {
    id: window
    width: Constants.width
    height: Constants.height
    visible: true
    title: "QFRCScouter"

    Universal.theme: Universal.Dark
    Universal.accent: config.object.qmlAccent

    MainScreen {
        id: screen

        anchors.fill: parent
    }
}
