import QtQuick 2.15
import QtQuick.Controls 2.15
import "qrc:/views/"
import Qt.labs.settings 1.0
import QtQuick.Layouts 1.15
import assets 1.0

Item {


    // NotificationManager {
    //     id: notificationManager
    //     anchors.fill: parent
    // }

    // Exemple de bouton pour tester la création de notification
    // Button {
    //     anchors.centerIn: parent
    //     text: "Create Test Notification"
    //     onClicked: {
    //         mainController.createNotification("Test notification from QML", "info")
    //     }
    // }

    Column{
        id: notificationColumn
        anchors{
            right: parent.right
            left: parent.left
            top: parent.top
            leftMargin: 10
            rightMargin: 10
            margins: 10
        }
        spacing: 10
        width: parent.width
        height: parent.height

        Repeater{
            model: mainController.unreadNotification

            NotificationItem{
                taskId: modelData.taskId
                message: modelData.message
                notificationId: modelData.id
                level: {
                    switch(modelData.level){
                        case "Task Deleted" : return "warning"
                        case "Task Overdue" : return "error"
                        default: return "info"
                    }
                }
            }
        }

        // Mark all as read (OPTIONAL, UNCOMMENT FOR FUTURE PURPOSE)
        // Rectangle {
        //     property color baseColor: Style.primary
        //     height: 40
        //     width: parent.width

        //     anchors{
        //         margins: 10
        //     }


        //     color: if(mouseArea.containsMouse){
        //                return Qt.darker(baseColor)
        //            }else{
        //                return baseColor
        //            }

        //     MouseArea{
        //         id: mouseArea
        //         anchors.fill: parent
        //         hoverEnabled: true
        //     }

        //     Text{
        //         text: "Mark all as read"
        //         anchors.centerIn: parent
        //     }
        // }
    }
}
