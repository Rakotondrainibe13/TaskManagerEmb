import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import components 1.0
import assets 1.0

Item {

    ScrollView {
        width: parent.width
        height: parent.height

        anchors.fill: parent

        Rectangle {
            id: subscriptionState

            anchors {
                fill: parent
                leftMargin: 50
                rightMargin: 50
                topMargin: 10
            }


            Rectangle{
                id: boxTittle
                height: 50
                //color: "#f0f0f0"
                anchors{
                    left: parent.left
                    right: parent.right
                    topMargin: 20
                }

                RowLayout{
                    spacing: 100
                    Text {
                        id: subscriptionTitleState
                        text: "Subscription State"
                        font.pixelSize: 20
                        font.bold: true
                        anchors {
                            topMargin: 18
                            top: parent.top
                            left: parent.left
                        }
                    }

                    Rectangle{
                        id: boxStatus
                        border.width: 1
                        border.color: mainController.ui_subscriptionManager.currentSubscriptions !== null ? "#00FF00" : "red"
                        color: "white"
                        width: mainController.ui_subscriptionManager.currentSubscriptions !== null ? 60 : 80
                        height: mainController.ui_subscriptionManager.currentSubscriptions !== null ? 60 : 80
                        radius: mainController.ui_subscriptionManager.currentSubscriptions !== null ? 60 : 80
                        Text {
                            id: textStatus
                            text: mainController.ui_subscriptionManager.currentSubscriptions !== null ? "Active" : "NO ACTIVE"
                            color: mainController.ui_subscriptionManager.currentSubscriptions !== null ? "#00FF00" : "red"
                            font.family: "Helvetica"
                            font.italic: true
                            font.bold: true
                            anchors.centerIn: parent
                        }

                    }
                }

            }

            Rectangle {
                id: currentSubscriptionBox

                height: 40

                anchors {
                    left: parent.left
                    right: parent.right
                    top: boxTittle.bottom
                    topMargin: 30
                }

                color: "#F0F0F0"

                RowLayout {
                    anchors.fill: parent
                    spacing: 10
                    Layout.alignment: Qt.AlignLeft

                    Text {
                        id: currentSubscriptionTitle
                        text: "Current Subscription"

                        font.pixelSize: 16
                        Layout.leftMargin: 40
                    }

                    Text {
                        id: subscriptionTypeName
                        text: mainController.ui_subscriptionManager.currentSubscriptionType

                        font.pixelSize: 16
                        font.bold: true
                    }
                }
            }

            Rectangle {
                id: subscriptionDurationDetailBox

                anchors {
                    top: currentSubscriptionBox.bottom
                    left: parent.left
                    right: parent.right
                }

                height: 100

                color: "#FDFDFD"

                RowLayout {
                    id: subscriptionDurationDetail

                    anchors.fill: parent

                    Item {
                        id: subscriptionStartItem

                        Layout.alignment: Qt.AlignTop
                        Layout.topMargin: 20
                        Layout.leftMargin: 40

                        Text {
                            id: subscriptionStartTitle

                            text: "Start date :"
                            font.pixelSize: 16

                            anchors {
                                top: parent.top
                                left: parent.left
                            }

                        }

                        Text {
                            id: subscriptionStartValue

                            text: mainController.ui_subscriptionManager.startDate
                            font.pixelSize: 16
                            font.bold: true

                            anchors {
                                top: subscriptionStartTitle.bottom
                                left: parent.left
                                topMargin: 20
                            }
                        }
                    }

                    Item {
                        id: subscriptionEndItem

                        Layout.alignment: Qt.AlignTop
                        Layout.topMargin: 20
                        Layout.leftMargin: 40

                        Text {
                            id: subscriptionEndTitle

                            text: "End date :"
                            font.pixelSize: 16

                            anchors {
                                top: parent.top
                                left: parent.left
                            }
                        }

                        Text {
                            id: subscriptionEndValue

                            text: mainController.ui_subscriptionManager.endDate
                            font.pixelSize: 16
                            font.bold: true

                            anchors {
                                top: subscriptionEndTitle.bottom
                                left: parent.left
                                topMargin: 20
                            }
                        }
                    }
                }
            }

            Button {
                id: newSubscriptionButton

                text: "New Subscription"
                font.bold: true

                anchors {
                    top: subscriptionDurationDetailBox.bottom
                    topMargin: 40
                    left: parent.left
                }

                height: 35
                leftPadding: 40
                rightPadding: 40
                font.pixelSize: 16

                background: Rectangle {
                    color: newSubscriptionMouseArea.containsMouse ? Qt.darker("lightblue") : "lightblue";
                    radius: 3
                }

                MouseArea {
                    id: newSubscriptionMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                      mainController.ui_navigationController.onGoSubscriptionCreateScreen()
                    }
                }

            }

            // Line divider
            Rectangle {
                id: lineDivider
                height: 1
                color: "lightgray"

                anchors {
                    top: newSubscriptionButton.bottom
                    left: parent.left
                    right: parent.right
                    topMargin: 40
                }
            }

            Text {
                id: subscriptionsListTitle
                text: "Subscription History"
                font.pixelSize: 20
                font.bold: true
                anchors {
                    topMargin: 40
                    top: lineDivider.bottom
                    left: parent.left
                }
            }

            Item {
                id: subscriptionListHistoryHeader

                anchors {
                    top:  subscriptionsListTitle.bottom
                    topMargin: 30
                    left: parent.left
                    right: parent.right
                }

                height: 30

                RowLayout {
                    anchors {
                        fill: parent
                    }

                    spacing: 10

                    Rectangle {
                        Layout.fillWidth: true

                        Text {
                            text: "Start date"

                            font.pixelSize: 14
                            font.bold: true
                            color: "gray"

                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true

                        Text {
                            text: "End date"

                            font.pixelSize: 14
                            font.bold: true
                            color: "gray"

                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true

                        Text {
                            text: "Subscription Type"

                            font.pixelSize: 14
                            font.bold: true
                            color: "gray"

                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true

                        Text {
                            text: "Status"

                            font.pixelSize: 14
                            font.bold: true
                            color: "gray"

                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }

                }

                // Line divider
                Rectangle {
                    id: subscriptionHistoryLineDivider
                    height: 1
                    color: "lightgray"

                    anchors {
                        top: subscriptionListHistoryHeader.bottom
                        left: parent.left
                        right: parent.right
                        topMargin: 10
                    }
                }

                // Subscription history row
                ListView {
                    anchors {
                        top: subscriptionHistoryLineDivider.bottom
                        topMargin: 10
                        left: parent.left
                        right: parent.right
                    }

                    height: 50

                    model: mainController.ui_subscriptionManager.ui_subscriptionList
                    delegate: SubscriptionHistoryRow {
                        startDate: Qt.formatDateTime(modelData.startDate, "dd/MM/yyyy")
                        endDate: Qt.formatDateTime(modelData.endDate, "dd/MM/yyyy")
                        type: modelData.subscriptionType.subscriptionName
                        status: modelData.status

                        onClicked: {
                            mainController.ui_navigationController.goSubscriptionDetailScreen(modelData.id)
                        }
                    }
                }

            }

        }
    }



}
