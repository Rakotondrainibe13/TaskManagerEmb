import QtQuick 2.15
import "qrc:/views/"
import QtQuick.Controls 2.15
Item {
    id: root
    
    property int maxNotifications: 5
    
    
    Connections {
        target: mainController
        function onNotificationCreated(message, level) {
            showNotification(message, level)
        }
    }

    function showNotification(message, level) {
        var component = Qt.createComponent("qrc:/views/NotificationItem.qml");
        if (component.status === Component.Ready) {
            var notification = component.createObject(notificationColumn, {
                "message": message,
                "level": level
            });

            if (notification) {
                if (notificationColumn.children.length > maxNotifications) {
                    notificationColumn.children[0].destroy();
                }
            } else {
                console.log("Error: Failed to create NotificationItem.");
            }
        } else {
            console.log("Error: Component creation failed:", component.errorString());
        }
    }
    
    Column {
        id: notificationColumn
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 10
        width: parent.width
        height: parent.height
        anchors.leftMargin : 10
        anchors.rightMargin : 10
    }

}
