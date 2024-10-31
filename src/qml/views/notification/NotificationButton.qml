import QtQuick 2.9
import assets 1.0

Item {
    property alias description: textDescription.text
    property color hoverColour: Style.backgroundSecondary
    property int notificationCount: mainController.countNotification
    
    signal navigationButtonClicked()

    width: parent.width
    height: 50

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.backgroundPrincipale

        Image {
            source: Style.iconNotificationBase64
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right   
            // anchors.rightMargin: 10
            cache: true
        }
        Text {
            id: textDescription
            width: 50
            height: 50
            color: notificationCount == 0 ? Style.textColor : Style.danger
            text: "Notification ("+notificationCount+")"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 13
            anchors.left: parent.left
            anchors.leftMargin:10  
        }
        

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: navigationButtonClicked()
        }

        states: [
            State {
                name: "hover"
            }
        ]
    }
}
