import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import QFRCScouter

Rectangle {
    id: scalePage

    signal clear

    property bool doClear: false

    color: Constants.bg

    TitleBanner {
        id: banner
        title: "Your Opinions"
    }

    property list<var> values

    ColumnLayout {
        uniformCellSizes: true

        anchors {
            top: banner.bottom
            bottom: parent.bottom

            topMargin: 8
            bottomMargin: 8

            left: parent.left
            right: parent.right
        }

        Repeater {
            model: scalesModel

            delegate: ScaleItem {
                Layout.preferredHeight: 100
                Layout.fillWidth: true

                bindTarget: scalePage
                bindedProperty: "values"

                Component.onCompleted: {
                    scalePage.clear.connect(() => clear())
                }
            }
        }
    }
}
