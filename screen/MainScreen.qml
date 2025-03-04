import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import QFRCScouter

import QtQuick.Controls.Universal

Rectangle {
    id: screen
    width: Constants.width
    height: Constants.height
    color: Constants.bg

    function resetScalar() {
        Constants.scalar = Math.max(width / Constants.width,
                                    height / Constants.height)
        Constants.isVertical = width < height
    }

    Component.onCompleted: {
        resetScalar()
    }

    onWidthChanged: resetScalar()
    onHeightChanged: resetScalar()

    SwipeView {
        id: swipe

        currentIndex: 0

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: buttons.top

            margins: 8
        }

        WelcomePage {
            id: welcome

            onBackToCode: {
                auto.doClear = false
                tele.doClear = false

                match.match--

                swipe.currentIndex = swipe.count - 1
            }
        }

        MatchInfo {
            id: match
        }

        PhasePage {
            id: auto
            model: autoModel
            title: "Autonomous"
        }

        PhasePage {
            id: tele
            model: teleModel
            title: "Teleoperated"
        }

        // ScalesPage {
        //     id: scales
        // }

        // NotesPage {
        //     id: notes
        // }
        QRCode {
            id: qr
        }
    }

    function getTsv() {
        let tsv = []
        tsv = match.tsv().concat(auto.values.concat(tele.values))
        return tsv
    }

    RowLayout {
        id: buttons

        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right

            margins: 5
        }

        height: parent.height / 8

        NavButton {
            text: "Back"
            onClicked: {
                --swipe.currentIndex
                if (swipe.currentIndex < 0)
                    swipe.currentIndex = 0
            }
        }

        ColumnLayout {
            Layout.fillWidth: true

            Text {
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter

                font {
                    bold: true
                    pixelSize: 25 * Constants.scalar
                }

                text: match.station
                color: text.includes("Red") ? "red" : "blue"
            }

            Text {
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter

                font {
                    bold: true
                    pixelSize: 25 * Constants.scalar
                }

                text: "Team " + match.team
                color: Constants.text
            }
        }

        NavButton {
            text: "Next"
            onClicked: {
                ++swipe.currentIndex

                if (swipe.currentIndex === swipe.count - 1) {
                    qr.tsv = getTsv()
                }

                if (swipe.currentIndex >= swipe.count) {
                    swipe.currentIndex = 0
                    match.match++
                    getTsv()

                    auto.doClear = true
                    tele.doClear = true

                    welcome.backAvailable = true
                }

                if (swipe.currentItem.doClear) {
                    swipe.currentItem.clear()
                    swipe.currentItem.doClear = false
                }
            }
        }
    }
}
