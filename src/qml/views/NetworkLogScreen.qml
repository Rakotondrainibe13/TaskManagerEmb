import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    visible: true
    width: parent.width
    height: 400

    Rectangle {
        anchors.fill: parent
        color: "white"

        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            anchors.margins: 20

            Text {
                text: "NETWORK LOGS"
                font.pointSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            ComboBox {
                model: ["TCP", "UDP"]
                width: 100
                Layout.alignment: Qt.AlignLeft
            }

            ListView {
                Layout.fillWidth: true
                height: 100
                model: ListModel {
                    Component.onCompleted: {
                        var logs = networkManager.getLogs();
                        for (var i = 0; i < logs.length; i++) {
                            append(logs[i]);
                        }
                    }
                }
                delegate: Rectangle {
                    width: parent.width
                    height: 30
                    color: index % 2 == 0 ? "lightgray" : "white"  // Alternance des couleurs pour les lignes

                    GridLayout {
                        columns: 4
                        anchors.fill: parent
                        anchors.margins: 1

                        Text {
                            text: model.timestamp
                            font.pointSize: 14
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignLeft
                        }

                        Text {
                            text: server
                            font.pointSize: 14
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignLeft
                        }

                        Text {
                            text: status
                            font.pointSize: 14
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignLeft
                        }

                        Text {
                            text: response
                            font.pointSize: 14
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignLeft
                        }
                    }
                }

                // Header Row for the Table
                header: Row {
                    width: parent.width
                    height: 30
                    Rectangle {
                        width: parent.width
                        height: 30
                        color: "darkgray"

                        GridLayout {
                            columns: 4
                            anchors.fill: parent
                            anchors.margins: 5

                            Text {
                                text: "timestamp"
                                font.bold: true
                                color: "white"
                                Layout.alignment: Qt.AlignLeft
                            }

                            Text {
                                text: "serverIP"
                                font.bold: true
                                color: "white"
                                Layout.alignment: Qt.AlignLeft
                            }

                            Text {
                                text: "status"
                                font.bold: true
                                color: "white"
                                Layout.alignment: Qt.AlignLeft
                            }

                            Text {
                                text: "response"
                                font.bold: true
                                color: "white"
                                Layout.alignment: Qt.AlignLeft
                            }
                        }
                    }
                }
            }
        }
    }
}
