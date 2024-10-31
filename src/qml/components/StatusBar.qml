import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import assets 1.0

Rectangle {
    id: idStatusBar
    height: Style.statusBarHeigth
    color: Style.backgroundPrincipale // Remplacez par Style.backgroundSecondary si défini ailleurs
    anchors {
        left: parent.left
        right: parent.right
        top: parent.top
    }

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome-webfont.ttf"
    }
    Connections {
        target: mainController.synchManager
        onSynchCompleted: {
            synchCompleted.text = response;
            synchCompleted.open();
        }
    }
    RowLayout {
        id: idRowLayout
        height: idStatusBar.height
        anchors {
            left: idStatusBar.left
            top: idStatusBar.top

        }
        spacing: 40 // Espace entre les éléments

        MenuBar {
            id: menuBar
            height: 40
            font.pixelSize: Style.sizeTextStatusBar
            background: Rectangle {
                color: Style.backgroundPrincipale // Remplacez par Style.backgroundSecondary si défini ailleurs
            }
            Menu {
                title: "File"

                MenuItem {
                    text: qsTr("&New task")
                    onTriggered: {
                        console.log("Add Student clicked")
                        mainController.ui_navigationController.goCreateTaskScreen();
                    }
                }

                MenuItem {
                    text: qsTr("&Task list")
                    onTriggered: {
                        console.log("Add Student clicked")
                        mainController.ui_navigationController.goListTaskScreen();
                    }
                }
            }
            Menu {
                title: "Edit"
            }

            // Menu {
            //     title: "File"
            // }
            // Menu {
            //     title: "Edit"
            // }
            Menu {
                title: "Options"
            }
            Menu {
                title: "Tools"
                MenuItem {
                    text: "Network Configuration"
                    onTriggered: mainController.ui_navigationController.goNetworkConfigScreen();
                }
                MenuItem {
                    text: "Network Monitoring"
                    onTriggered: mainController.ui_navigationController.goNetworkMonitoringScreen();
                }
                MenuItem {
                    text: "Network Logs"
                    onTriggered: mainController.ui_navigationController.goNetworkLogScreen();
                }
                MenuItem {
                    text: "Retention configuration"
                    onTriggered: mainController.ui_navigationController.goRetentionConfigScreen();
                }
                
            }
            Menu {
                title: "Window"
            }
            Menu {
                title: "Help"
            }
        }

        Repeater {
            model: statusBarText
            delegate:
                Rectangle {
                color: Style.secondary // Fond transparent
                Layout.preferredHeight: idStatusBar.height

                Text {
                    text: model.text
                    color: Style.textColor
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        right: parent.right
                        leftMargin: 20
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Mouse clicked")
                        }
                    }
                }
            }
        }
    }

    RowLayout {
        id: idButtonSyncLayout
        height: idStatusBar.height
        width: 100
        anchors {
            right: idRightRowLayout.left
            top: idStatusBar.top
            rightMargin: 10
        }
        spacing: 10

        Button {
            id: idButtonSync
            text: "Start Synch"
            onClicked: { 
                mainController.doSync()
            }
        }

    }

    RowLayout {
        id: idRightRowLayout
        height: idStatusBar.height
        width: 150
        anchors {
            right: idUserRowLayout.left
            top: idStatusBar.top
            rightMargin: 10
        }
        spacing: 10

        NotificationButton{
                hoverColour: Style.primary
                onNavigationButtonClicked: mainController.ui_navigationController.goNotificationScreen();
        }

    }

    RowLayout {
        id: idUserRowLayout
        height: idStatusBar.height
        width: 50
        anchors {
            // left : idRightRowLayout.right
            right: idStatusBar.right
            top: idStatusBar.top
        }
        // spacing: 10

        Rectangle {
            id: background
            anchors.fill: parent
            color: Style.backgroundPrincipale


            Image {
                source: Style.iconLogoutBase64
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 20
                cache: true
            }


            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true
                onEntered: background.state = "hover"
                onExited: background.state = ""
                onClicked: {
                    confirmationDialog.open()
                }
            }

            states: [
                State {
                    name: "hover"
                }
            ]

            MessageDialog {
                id: confirmationDialog
                text: "Confirmation"
                informativeText: "Do you really want to leave?"
                buttons: MessageDialog.Ok | MessageDialog.Cancel

                onAccepted: mainController.logout()
            }
            MessageDialog {
                id: synchCompleted
                text: "Confirmation"
                buttons: MessageDialog.Ok
            }
        }
    }
}
