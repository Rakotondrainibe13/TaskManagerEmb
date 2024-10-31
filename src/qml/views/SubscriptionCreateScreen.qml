import QtQuick 2.9
import QtQuick.Controls 2.15
import components 1.0
import assets 1.0
import Qt.labs.settings 1.0
import QtQuick.Dialogs
Item {
    id: root
    property int subscriptionTypeId: -1
    property int selectedCardId: -1


    function setSubscriptionTypeId(id) {
        subscriptionTypeId = id
    }

    function setSelectedCardId(id) {
            selectedCardId = id
    }


    Rectangle {
        id: idCreateSubscription
        width: parent.width
        anchors.fill: parent
        color: Style.colourBackGround

        Rectangle {
            id: titlePage
            width: idCreateSubscription.width
            height: 60
            anchors.top: idCreateSubscription.top
            anchors.left: idCreateSubscription.left

            Text {
                id: title
                text: "Subscription Paiement"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 20
                font {
                    family: Style.fontHelvetica
                    pixelSize: 24
                    bold: true
                }
            }

            Rectangle {
                id: columnPage
                width: parent.width
                anchors.top: titlePage.bottom
                anchors.topMargin: 20

                Column {
                    width: parent.width
                    spacing: 10

                    Text {
                        id: subscriptionTypeText
                        text: "Subscription Types"
                        font {
                            family: Style.fontHelvetica
                            pixelSize: 18
                        }
                        anchors.left: parent.left
                        anchors.leftMargin: 40
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Grid {
                        columns: 2
                        spacing: 10
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.topMargin: 0
                        anchors.leftMargin: 50
                        anchors.bottomMargin: 10

                        Repeater {
                            model: mainController.ui_subscriptionManager.ui_subscriptionType

                            SubscriptionTypeCard {
                                nameSubscription: modelData.subscriptionName
                                durationSubscription: modelData.duration + " Days"
                                priceSubscription: modelData.price + " Euro"
                                property int cardId: modelData.id
                                colorClicked: root.selectedCardId === cardId ? "lightgray" : "white"
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        root.setSubscriptionTypeId(modelData.id)
                                        root.setSelectedCardId(modelData.id)
                                    }
                                }
                            }
                        }
                    }

                    // Quantity Text
                    Text {
                        id: quantitySubscriptionTitle
                        text: "Quantity"
                        font {
                            family: Style.fontHelvetica
                            pixelSize: 18
                        }
                        anchors.topMargin: 20
                        anchors.left: parent.left
                        anchors.leftMargin: 40
                        horizontalAlignment: Text.AlignHCenter
                    }

                    TextField {
                        id: quantitySubscription
                        width: parent.width / 3
                        height: 40
                        placeholderText: "Enter Quantity"
                        inputMethodHints: Qt.ImhDigitsOnly
                        font.pixelSize: 16
                        color: "black"
                        padding: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 40
                    }

                    Grid {
                        columns: 2
                        spacing: 20
                        anchors.left: parent.left
                        anchors.leftMargin: 40
                        anchors.topMargin: 40

                        Button {
                            id: newSubscriptionButton
                            text: "Back"
                            font.bold: true
                            height: 35
                            width: 100
                            font.pixelSize: 16

                            background: Rectangle {
                                color: newSubscriptionMouseArea.containsMouse ? Qt.darker("lightgrey") : "lightgrey";
                                radius: 3
                            }

                            MouseArea {
                                id: newSubscriptionMouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor

                                onClicked: {
                                    mainController.ui_navigationController.onGoSubscriptionStateScreen()
                                }
                            }
                        }

                        Button {
                            id: backButton
                            text: "Save"
                            font.bold: true
                            height: 35
                            width: 100
                            font.pixelSize: 16

                            background: Rectangle {
                                color: backMouseArea.containsMouse ? Qt.darker("lightblue") : "lightblue";
                                radius: 3
                            }

                            MouseArea {
                                id: backMouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor

                                onClicked: {
                                    confirmationDialog.open()
                                }
                            }
                        }

                        MessageDialog{
                            id: confirmationDialog
                            text: "Confirmation"
                            informativeText: "Do you create a new Subscription"
                            buttons: MessageDialog.Ok | MessageDialog.Cancel

                            onAccepted: {
                                mainController.ui_subscriptionManager.createSubscription(subscriptionTypeId,quantitySubscription.text)
                                quantitySubscription.text = ""
                                setSubscriptionTypeId(-1)
                                mainController.ui_navigationController.onGoSubscriptionStateScreen()
                            }
                        }
                    }
                }
            }
        }
    }
}
