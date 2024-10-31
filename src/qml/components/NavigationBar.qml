import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.12
import Qt.labs.settings 1.0
import QtQuick.Dialogs

Item {
    property bool isCollapsed: true
    property bool is_subscribed: false



    function checkSubscriptionStatus() {
        if (mainController.ui_subscriptionManager.currentSubscriptions === null) {
            is_subscribed = false;
        } else {
            is_subscribed = true;
        }
    }

    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome-webfont.ttf"
    }

    anchors {
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }
    width: 150

    Rectangle {
        anchors.fill: parent
        color: Style.backgroundPrincipale

        Column {
            width: parent.width

            NavigationButton {
                iconCharacter: "\uf015"
                description: "Home"
                hoverColour: "#8aef63"
                // visible: mainController.hasAccess("Dashboard")
                onNavigationButtonClicked: {
                    mainController.ui_navigationController.goListTaskScreen();
                }
            }

            NavigationButton {
                iconCharacter: "\uf15b"
                description: "New Task"
                hoverColour: "#8aef63"
                // visible: mainController.hasAccess("NewTask")
                onNavigationButtonClicked: {
                    mainController.ui_navigationController.goCreateTaskScreen();
                }
            }

            NavigationButton {
                iconCharacter: "\uf03a"
                description: "Lists Task"
                hoverColour: "#8aef63"
                // visible: mainController.hasAccess("ListTask")
                onNavigationButtonClicked: {
                    mainController.ui_navigationController.goListTaskScreen();
                }
            }

            NavigationButton {
                iconCharacter: "\uf073"
                description: "Calendar"
                hoverColour: "#8aef63"
                // visible: mainController.hasAccess("Calendar")
                onNavigationButtonClicked: {
                    checkSubscriptionStatus();
                    onNavigationButtonClicked: {
                        if (!is_subscribed) {
                            subscriptionDialog.open();
                        } else {
                            mainController.ui_navigationController.goCalendarScreen();
                        }
                    }
                }
            }
            NavigationButton {
                iconCharacter: "\uf007"
                description: "Profiles"
                hoverColour: "#8aef63"
                // visible: mainController.hasAccess("ListUser")
                onNavigationButtonClicked: {
                    mainController.ui_navigationController.goUserScreen();
                }
            }

            NavigationButton {
                iconCharacter: "\uf09d"
                description: "Subscriptions"
                hoverColour: "#8aef63"
                onNavigationButtonClicked: {
                    mainController.ui_navigationController.goSubscriptionStateScreen();
                }
            }
            
            NavigationButton {
                iconCharacter: "\uf080"
                description: "Statistic"
                hoverColour: "#8aef63"
                // visible: mainController.hasAccess("ListUser")
                onNavigationButtonClicked: {
                    checkSubscriptionStatus();
                    if(!is_subscribed){
                        subscriptionDialog.open();
                    }else{
                        mainController.ui_navigationController.goStatisticScreen();
                    }
                }
            }
        }
        MessageDialog{
            id: subscriptionDialog
            text: "No Active Subscription"
            informativeText: "You need to go to the Subscription State to manage your subscriptions."
            buttons: MessageDialog.Ok | MessageDialog.Cancel
            onAccepted: {
                mainController.ui_navigationController.goSubscriptionStateScreen();
            }
        }
    }
}
