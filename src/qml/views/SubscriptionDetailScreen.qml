import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    property int id
    property var subscriptionDetails

    Component.onCompleted: {
        var subscription = mainController.ui_subscriptionManager.findSubscription(id)
        if (subscription) {
            subscriptionDetails = subscription
        } else {
            console.log("Subscription with ID " + id + " not found !")
        }
    }

    Rectangle {
        id: subcriptionDetail

        anchors.fill: parent

        anchors {
            fill: parent
            margins: 50
        }

        Rectangle {
            id: subscriptionDetailContent

            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            height: 340

            radius: 10
            border.color: "#F0F0F0"

            Text {
                id: subscriptionId
                text: "Subcription N° " + subscriptionDetails.id
                font.bold: true
                font.pixelSize: 20
                color: "#1E2128"

                anchors {
                    top: parent.top
                    left: parent.left
                    leftMargin: 40
                    topMargin: 40
                }
            }

            Text {
                id: subscriptionDescription
                text: "You made a <b>" + subscriptionDetails.subscriptionType.subscriptionName + "</b> on <font color='#379AE6'> " + Qt.formatDate(subscriptionDetails.subscriptionDate, 'dd MMMM yyyy')  + "</font>. You can access all the features of the application."

                font.pixelSize: 16
                color: "#323743"

                width: subscriptionDetailContent.width * 0.7
                wrapMode: Text.WordWrap
                textFormat: Text.RichText

                anchors {
                    top: subscriptionId.bottom
                    topMargin: 20
                    left: subscriptionId.left
                }
            }

            Text {
                id: subscriptionDuration
                text: "From " + Qt.formatDate(subscriptionDetails.startDate, 'dd MMMM yyyy')  + " to " + Qt.formatDate(subscriptionDetails.endDate, 'dd MMMM yyyy')
                font.pixelSize: 14
                color: "#9095A1"

                anchors {
                    top: subscriptionDescription.bottom
                    topMargin: 20
                    left: subscriptionDescription.left
                }
            }

            Text {
                id: price
                text: subscriptionDetails.price.toLocaleString(Qt.locale("fr_FR"), "f", 2) + " Euro"

                font.pixelSize: 18
                font.bold: true
                color: '#1E2128'

                anchors {
                    top: subscriptionDuration.top
                    topMargin: 40
                    left: subscriptionDuration.left
                }
            }

            Button {
                id: backButton

                text: "Back"
                font.bold: true

                anchors {
                    top: price.bottom
                    topMargin: 60
                    left: price.left
                }

                height: 35
                leftPadding: 40
                rightPadding: 40
                font.pixelSize: 16

                background: Rectangle {
                    color: backButtonMouseArea.containsMouse ? Qt.darker("lightblue") : "lightblue";
                    radius: 3
                }

                MouseArea {
                    id: backButtonMouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        mainController.ui_navigationController.goSubscriptionStateScreen();
                    }
                }

            }

        }

    }

}
