import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0

Item {
    property alias title: titleTask.text
    property alias dateTask: idDateTask.text
    property int taskId

    height: 125
    width: parent.width - 20
    anchors.horizontalCenter: parent.horizontalCenter



    Rectangle{
        id: idTask
        height: parent.height
        width: parent.width
        border.color: Style.borderLineSecondary
        color: Style.backgroundSecondary
        border.width: 2

        Text {
            id: titleTask
            font.pixelSize: 20
            anchors {
                top: parent.top
                topMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
        }
        Text {
            id: idDateTask
            font.pixelSize: 15
            anchors {
                // top: titleTask.bottom
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }
        }

        Button {
            text: qsTr("Show")
            width: 100
            onClicked: {
                mainController.ui_navigationController.goDetailTaskScreen(taskId);
            }
            anchors {
                top: idDateTask.bottom
                topMargin: 10
                left: parent.left
                leftMargin: 20
                // horizontalCenter: parent.horizontalCenter
            }
            background: Rectangle {
                color: Style.third
                radius: Style.borderRadiusField
                border.width: 1
                border.color: Style.borderLineSecondary
            }
        }
        Button {
            text: qsTr("Execute")
            width: 100
            onClicked: {
                console.log(taskId)
                mainController.executeTask(taskId)
            }
            anchors {
                top: idDateTask.bottom
                topMargin: 10
                right: parent.right
                rightMargin: 20
                // horizontalCenter: parent.horizontalCenter
            }
            background: Rectangle {
                color: Style.secondary
                radius: Style.borderRadiusField
                border.width: 1
                border.color: Style.borderLineSecondary
            }
        }

    }

}
