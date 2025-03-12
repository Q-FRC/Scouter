import QtQuick
import QtQuick.Controls

import QFRCScouter

Rectangle {
    color: Constants.bg

    property list<var> tsv: ["blank"]

    TitleBanner {
        id: banner
        title: "QR Code"
    }

    Image {
        source: "image://QZXing/encode/" + tsv.join("\t") + "?border=true"
        cache: false

        anchors {
            top: banner.bottom
            bottom: parent.bottom

            left: parent.left
            right: parent.right

            margins: 100 * Constants.scalar
        }

        fillMode: Image.PreserveAspectFit

        sourceSize.width: Math.min(width, height)
        sourceSize.height: Math.min(width, height)
    }
}
