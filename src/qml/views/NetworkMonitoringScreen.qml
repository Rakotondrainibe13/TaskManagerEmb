import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtCharts 2.15

Item {
    visible: true
    width: parent.width
    height: 600

    Rectangle {
        anchors.fill: parent
        color: "white"
        anchors.margins: 20

        ScrollView {
            anchors.fill: parent

            ColumnLayout {
                spacing: 20
                Layout.margins: 20

                // Title
                Label {
                    text: "NETWORK MONITORING"
                    font.pointSize: 20
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                // Connection Status Section
                GroupBox {
                    title: "Connection Status"
                    Layout.fillWidth: true

                    GridLayout {
                        columns: 2
                        rowSpacing: 10
                        columnSpacing: 20

                        Label { text: "TCP Connection:" }
                        Label { text: "Connected" }  // This would be dynamic

                            Label { text: "UDP Connection:" }
                            Label { text: "Disconnected" }  // This would be dynamic
                            }
                        }


                        ListView {
                            Layout.fillWidth: true
                            height: 100
                            model: ListModel {
                                ListElement { command: "ConnectCommand"; details: "TCP 192.168.1.1:8080" }
                                ListElement { command: "SendDataCommand"; details: "Data sent via TCP" }
                                ListElement { command: "DisconnectCommand"; details: "TCP Disconnected" }
                            }

                            delegate: Rectangle {
                                width: parent.width
                                height: 30
                                color: index % 2 == 0 ? "lightgray" : "white"  // Alternance des couleurs pour les lignes

                                GridLayout {
                                    columns: 2
                                    anchors.fill: parent
                                    anchors.margins: 5

                                    Text {
                                        text: command
                                        font.pointSize: 14
                                        Layout.alignment: Qt.AlignLeft
                                    }

                                    Text {
                                        text: details
                                        font.pointSize: 14
                                        Layout.alignment: Qt.AlignRight
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
                                        columns: 2
                                        anchors.fill: parent
                                        anchors.margins: 5

                                        Text {
                                            text: "Command"
                                            font.bold: true
                                            color: "white"
                                            Layout.alignment: Qt.AlignLeft
                                        }

                                        Text {
                                            text: "Details"
                                            font.bold: true
                                            color: "white"
                                            Layout.alignment: Qt.AlignRight
                                        }
                                    }
                                }
                            }
                        }

                        // Packet Details Section
                        GroupBox {
                            title: "Packet Details"
                            Layout.fillWidth: true

                            GridLayout {
                                columns: 2
                                rowSpacing: 10
                                columnSpacing: 20

                                Label { text: "Last Packet Received:" }
                                Label { text: "[Data]" }  // This would be dynamic

                                    Label { text: "Last Packet Sent:" }
                                    Label { text: "[Data]" }  // This would be dynamic
                                    }
                                }

                            }
                        }
                    }
                }
