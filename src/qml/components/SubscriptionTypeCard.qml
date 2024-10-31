import QtQuick 2.9

Item {
    property alias nameSubscription: nameSubscription.text
    property alias durationSubscription: durationSubscription.text
    property alias priceSubscription: priceSubscription.text
    property alias colorClicked : idSubscriptionType.color


    height: 100
    width: (parent.width - 50)/2

    Rectangle {
        id: idSubscriptionType
        height: parent.height
        width: parent.width
        border.color: "lightgrey"
        border.width: 0.5
        radius: 10

        anchors {
            top: parent.top

        }

        //color: "white"

        Rectangle {
            id: hoverOverlay
            anchors.fill: parent
            color: "lightgrey"
            opacity: 0
            radius: 10

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true

                onEntered: hoverOverlay.opacity = 0.5
                onExited: hoverOverlay.opacity = 0
            }
        }

        Column {
            anchors.fill: parent
            anchors.margins: 10

            spacing: 10
            anchors.centerIn: parent

            Text {
                id: nameSubscription
                font.pixelSize: 18
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                id: durationSubscription
                font.pixelSize: 18
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                id: priceSubscription
                font.pixelSize: 18
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
