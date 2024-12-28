import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.6

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
        anchors {
            top: banner.bottom
            bottom: parent.bottom

            topMargin: 8 * Constants.scalar
            bottomMargin: 8 * Constants.scalar

            left: parent.left
            right: parent.right
        }

        Repeater {
            model: scalesModel

            delegate: ScaleItem {
                Layout.preferredHeight: 100 * Constants.scalar
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
