import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QFRCScouter

Rectangle {
    function clear() {
        // clear is a no-op here
    }

    id: matchInfo

    property string initials
    property int match: 1
    property int team
    property string station: "Red 1"

    property string event

    color: Constants.bg

    function tsv() {
        return [initials, match, team]
    }

    ErrorDialog {
        id: fail
        title: "Download Failed"
        text: "Downloading schedule failed. Check your network connection."
    }

    ErrorDialog {
        id: failWrite
        title: "Download Failed"
        text: "Downloading schedule succeeded, but writing schedule to disk failed. Check your home directory permissions."
    }

    ErrorDialog {
        id: invalidCode
        title: "Download Failed"
        text: "Invalid event code."
    }

    ErrorDialog {
        id: success
        title: "Download Succeeded"
        text: "Downloading schedule succeeded. Set your alliance station and the app will automatically select the right team for each match."
    }

    Component.onCompleted: {
        matchData.failed.connect(() => fail.open());
        matchData.failedWrite.connect(() => failWrite.open());
        matchData.invalidCode.connect(() => invalidCode.open());
        matchData.successful.connect(() => {
                                         team = matchData.getTeam(station, match)
                                         success.open()
                                     });
    }

    TitleBanner {
        id: banner
        title: "Match Info"
    }

    ColumnLayout {
        anchors {
            top: banner.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom

            topMargin: 8
            bottomMargin: 8
        }

        LabeledTextField {
            Layout.fillWidth: true
            Layout.preferredHeight: 80

            label: "Scouter Initials"

            bindTarget: matchInfo
            bindedProperty: "initials"
        }

        LabeledSpinBox {
            Layout.fillWidth: true
            Layout.preferredHeight: 80

            label: "Match Number"
            from: 1
            to: 200

            bindTarget: matchInfo
            bindedProperty: "match"

            onValueChanged: team = matchData.getTeam(station, match)
        }

        LabeledSpinBox {
            Layout.fillWidth: true
            Layout.preferredHeight: 80

            label: "Team Number"
            to: 99999

            bindTarget: matchInfo
            bindedProperty: "team"
        }

        RowLayout {
            visible: !platform.isWeb();
            Layout.fillWidth: true
            Layout.preferredHeight: 80

            LabeledTextField {
                Layout.fillWidth: true
                Layout.preferredHeight: 80

                label: "Event Code"

                bindTarget: matchInfo
                bindedProperty: "event"
            }

            Button {
                Layout.preferredHeight: 80
                font.pixelSize: 30

                background: Rectangle {
                    radius: 5

                    color: parent.pressed ? Constants.buttonPressed : Constants.button
                }

                Universal.foreground: Constants.buttonText
                text: "Download Schedule"
                onClicked: matchData.downloadSchedule(matchInfo.event)
            }
        }

        LabeledComboBox {
            Layout.fillWidth: true
            Layout.preferredHeight: 80

            label: "Alliance Station"
            choices: [
                "Red 1", "Red 2", "Red 3",
                "Blue 1", "Blue 2", "Blue 3"
            ]

            onActivated: (index) => team = matchData.getTeam(station, match)

            bindTarget: matchInfo
            bindedProperty: "station"
        }
    }
}
