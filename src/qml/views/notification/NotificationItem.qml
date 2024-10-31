import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    width: parent.width
    height: 60
    color: "#E6E6E6"
    radius: 5

    property alias message: messageId.text
    property string level: "info" 
    property int taskId
    property int notificationId

    property string rectColor : {
                switch(root.level) {
                    case "info": return "#6C8EBF"
                    case "warning": return "#FFD700"
                    case "error": return "#FF0000"
                    default: return "#6C8EBF"
                }
            }

    MouseArea{

        anchors.fill: parent
        onClicked: {
            mainController.ui_navigationController.goDetailTaskScreen(taskId);
        }

        RowLayout {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 10

            Rectangle {
                width: 5
                Layout.fillHeight: true
                color:  root.rectColor
            }

            Text {
                id: messageId
                Layout.fillWidth: true
                font.pixelSize: 14
                wrapMode: Text.WordWrap
            }

            Button {
                text: "X"
                onClicked: {
                    mainController.readNotification(notificationId)
                    // console.log("I am clicked with id " + notificationId)
                    // root.destroy()
                }
            }

            Rectangle {
                width: 5
                Layout.fillHeight: true
                color:  root.rectColor
            }
        }
    }
}
