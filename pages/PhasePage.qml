import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

import Qt.labs.qmlmodels

import QFRCScouter

Rectangle {
    signal clear

    required property var model
    required property string title

    property bool doClear: false

    id: phase

    color: Constants.bg

    TitleBanner {
        id: banner
        title: phase.title
    }

    property list<var> values

    GridLayout {
        anchors {
            top: banner.bottom
            bottom: parent.bottom

            topMargin: 8
            bottomMargin: 8

            left: parent.left
            right: parent.right
        }

        uniformCellWidths: true

        columns: 2

        Repeater {
            model: phase.model

            delegate: DelegateChooser {
                role: "type"

                DelegateChoice {
                    roleValue: "int"

                    MatchSpinBox {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100 * Constants.scalar

                        bindTarget: phase
                        bindedProperty: "values"

                        Component.onCompleted: {
                            phase.clear.connect(() => value = 0)
                            phase.values.push(0)
                        }
                    }
                }

                DelegateChoice {
                    roleValue: "bool"

                    LabeledCheckbox {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 30 * Constants.scalar

                        bindTarget: phase
                        bindedProperty: "values"

                        Component.onCompleted: {
                            phase.clear.connect(() => control.checked = false)
                            phase.values.push(0)
                        }
                    }
                }
            }
        }
    }
}
