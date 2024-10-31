import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0
import QtQuick.Layouts 1.3

Item {
    id: root

    Rectangle {
        id: idUser
        width: parent.width
        height: parent.height
        color: Style.colourBackground
        anchors {
            leftMargin: 50
        }

        Rectangle {
            id: titlePage
            width: parent.width
            height: 60
            anchors.top: parent.top
            color: Style.white
            border.color: "#d3d3d3"
            Text {
                text: "User List"
                anchors.centerIn: parent
                font {
                    family: Style.fontHelvetica
                    pixelSize: 24
                    bold: true
                }
            }
        }

        ColumnLayout {
            anchors {
                top: titlePage.bottom
                left: parent.left
                right: parent.right
            }

            RowLayout {
                spacing: 10
                Rectangle {
                    width: root.width * 0.2
                    height: 40
                    color: "#d3d3d3"
                    border.color: "#a9a9a9"
                    Text {
                        text: "Pseudo"
                        anchors.centerIn: parent
                        font.bold: true
                    }
                }

                Rectangle {
                    width: root.width * 0.4
                    height: 40
                    color: "#d3d3d3"
                    border.color: "#a9a9a9"
                    Text {
                        text: "Email"
                        anchors.centerIn: parent
                        font.bold: true
                    }
                }

                Rectangle {
                    width: root.width * 0.2
                    height: 40
                    color: "#d3d3d3"
                    border.color: "#a9a9a9"
                    Text {
                        text: "Accès"
                        anchors.centerIn: parent
                        font.bold: true
                    }
                }

                Rectangle {
                    width: root.width * 0.2
                    height: 40
                    color: "#d3d3d3"
                    border.color: "#a9a9a9"
                    Text {
                        text: "Action"
                        anchors.centerIn: parent
                        font.bold: true
                    }
                }
            }

            Repeater {
                model: mainController.getUsersAsQObjects()

                delegate: RowLayout {
                    spacing: 10

                    Rectangle {
                        width: root.width * 0.2
                        height: 50
                        color: "#f0f0f0"
                        border.color: "#dcdcdc"
                        Text {
                            text: modelData.username
                            anchors.centerIn: parent
                        }
                    }

                    Rectangle {
                        width: root.width * 0.4
                        height: 50
                        color: "#f0f0f0"
                        border.color: "#dcdcdc"
                        Text {
                            text: modelData.email
                            anchors.centerIn: parent
                        }
                    }

                    Rectangle {
                        width: root.width * 0.2
                        height: 50
                        color: "#f0f0f0"
                        border.color: "#dcdcdc"
                        Text {
                            text: modelData.role === "r" ? "read" : "read + write"
                            anchors.centerIn: parent
                        }
                    }

                    Rectangle {
                        width: root.width * 0.2
                        height: 50
                        color: "#f0f0f0"
                        // border.color: "#dcdcdc"

                        Button {
                            text: modelData.role === "r" ? "Write" : "No Write"
                            anchors.centerIn: parent
                            background: Rectangle {
                                color: modelData.role === "r" ? "red" : "#4D7FA1"
                                radius: Style.borderRadiusField
                                // border.color: "#0056b3"
                                // border.width: 2
                            }
                            contentItem: Text {
                                text: modelData.role === "r" ? "Write" : "No Write"
                                color: "#ffffff"
                                // font.bold: true
                            }
                            onClicked: {
                                if (modelData.role === "r") {
                                    mainController.updateUserRole(modelData.userID,"rw");
                                    modelData.setRole("rw");
                                } else {
                                    mainController.updateUserRole(modelData.userID,"r");
                                    modelData.setRole("r");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
