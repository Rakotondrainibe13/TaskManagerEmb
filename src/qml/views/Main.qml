import QtQuick 2.15
import QtQuick.Controls 2.15
import components 1.0
import assets 1.0
import Qt.labs.settings 1.0
import QtQuick.Window 2.2

ApplicationWindow {
    visible: true
    width: WINDOW_WIDTH
    height: WINDOW_HEIGHT
    title: qsTr("Task Manager")

    property bool isLoginScreenVisible: true

    Connections {
        target: mainController.ui_navigationController
        onGoCreateTaskScreen: {
            isLoginScreenVisible = false
            contentFrame.replace("qrc:/views/TaskCreateScreen.qml")
        }
        onGoLoginScreen: {
            isLoginScreenVisible = true
            contentFrame.replace("qrc:/views/LoginScreen.qml")
        }
        onGoListTaskScreen: {
            isLoginScreenVisible = false
            contentFrame.replace("qrc:/views/TaskListScreen.qml")
        }
        onGoNotificationScreen: {
          isLoginScreenVisible = false
          contentFrame.replace("qrc:/views/NotificationScreen.qml")
       }
        onGoUserScreen: {
          isLoginScreenVisible = false
          contentFrame.replace("qrc:/views/UserScreen.qml")
       }
        onGoCalendarScreen: {
          isLoginScreenVisible = false
          contentFrame.replace("qrc:/views/EventCalendar.qml")
       }
       onGoRetentionConfigScreen: contentFrame.replace("qrc:/views/RetentionConfigScreen.qml")
        onGoStatisticScreen: {
          isLoginScreenVisible = false
          contentFrame.replace("qrc:/views/StatisticScreen.qml")
       }


        onGoNetworkConfigScreen: contentFrame.replace("qrc:/views/NetworkConfigScreen.qml")
        onGoNetworkMonitoringScreen: contentFrame.replace("qrc:/views/NetworkMonitoringScreen.qml")
        onGoNetworkLogScreen: contentFrame.replace("qrc:/views/NetworkLogScreen.qml")

        // Detail of the page
        onGoDetailTaskScreen: function(id){
            isLoginScreenVisible = false
            contentFrame.replace("qrc:/views/TaskDetailScreen.qml", { id: id })
        }

        // Edit a task
        onGoEditTaskScreen: function(id){
            isLoginScreenVisible = false
            contentFrame.replace("qrc:/views/TaskEditScreen.qml", { id: id })
        }

        // View subscription
        onGoSubscriptionStateScreen: function() {
            isLoginScreenVisible = false
            contentFrame.replace("qrc:/views/SubscriptionStateScreen.qml")
        }

        //vieew createSubscrition
        onGoSubscriptionCreateScreen: function () {
            isLoginScreenVisible = false
            contentFrame.replace("qrc:/views/SubscriptionCreateScreen.qml")
        }

        onGoSubscriptionDetailScreen: function(id) {
            isLoginScreenVisible = false
            contentFrame.replace("qrc:/views/SubscriptionDetailScreen.qml", {id: id})
        }
    }

    Rectangle {
        width: parent.width
        height: parent.height
        //color: Style.primary

        StatusBar {
            id: idStatusBar
            anchors.top: parent.top
            width: parent.width
            visible: !isLoginScreenVisible
        }

        NavigationBar {
            id: navigationBar
            anchors.top: idStatusBar.bottom
            visible: !isLoginScreenVisible
        }

        StackView {
            id: contentFrame
            anchors {
                top: idStatusBar.bottom
                bottom: idFooter.top
                right: parent.right
                left: navigationBar.right
            }
            initialItem: "qrc:/views/LoginScreen.qml"
            clip: true
        }

        FooterBar {
            id: idFooter
            // width: parent.width
            // anchors {
            //     left: parent.left
            //     right: parent.right
            //     bottom: parent.bottom
            // }
        }

    }
}

