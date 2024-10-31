import QtQuick 2.15
import assets 1.0

Item {
    width: parent.width
    height: Style.heigthBarFooter

    anchors {
        left: parent.left
        right: parent.right
        bottom: parent.bottom
    }
    Rectangle {
        width: parent.width
        height: parent.height
        color: Style.backgroundPrincipale

        Text {
            text: "©Copyright 2024"
            anchors.centerIn: parent
            color: Style.TextColor
            font.pixelSize: 12
        }
    }
}
