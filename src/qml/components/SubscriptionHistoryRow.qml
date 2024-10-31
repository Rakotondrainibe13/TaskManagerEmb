import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls

Rectangle {
    id: root

    property color cellColor: buttonMouseArea.containsMouse ? "#F0F0F0" : "transparent"

    property alias startDate : startDate.text
    property alias endDate: endDate.text
    property alias type: subscriptionType.text
    property alias status: subscriptionStatus.text

    signal clicked

    anchors {
        left: parent.left
        right: parent.right
    }

    color: root.cellColor

    height: 40

    RowLayout {
        anchors.fill: parent

        spacing: 10

        Rectangle {
            Layout.fillWidth: true
            height: 40
            color: root.cellColor

            Text {
                id: startDate

                font.pixelSize: 14
                color: "gray"

                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }

            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 40
            color: root.cellColor

            Text {
                id: endDate

                font.pixelSize: 14
                color: "gray"

                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 40
            color: root.cellColor

            Text {
                id: subscriptionType

                font.pixelSize: 14
                color: "gray"

                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 40
            color: root.cellColor

            Text {
                id: subscriptionStatus

                font.pixelSize: 14
                color: if(subscriptionStatus.text == "Completed") {
                           return "#E91313"
                       } else if (subscriptionStatus.text == "Active") {
                           return "#1DD75B"
                       } else {
                           return "#EFB034"
                       }

                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
            }
        }
    }

    MouseArea {
        id: buttonMouseArea

        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            root.clicked()
        }
    }
}
