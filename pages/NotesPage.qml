import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import QFRCScouter

Rectangle {
    function clear() {
        field.text = ""
    }

    function tsv() {
        // for some reason, using .replace() only replaces one
        return field.text.split("\n").join("; ")
    }

    property bool doClear: false

    id: notes

    color: Constants.bg

    TitleBanner {
        id: banner
        title: "Notes"
    }

    TextArea {
        id: field
        wrapMode: TextInput.Wrap

        anchors {
            top: banner.bottom
            bottom: parent.bottom

            topMargin: 8
            bottomMargin: 8

            left: parent.left
            right: parent.right
        }

        font.pixelSize: 25 * Constants.scalar

        color: Constants.text

        background: Rectangle {
            border.color: Constants.accent
            border.width: 2

            radius: 5
            color: Constants.bg
        }
    }
}
