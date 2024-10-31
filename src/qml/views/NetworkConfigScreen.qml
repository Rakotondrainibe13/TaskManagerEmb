import QtQuick 2.9
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Controllers 1.0
import assets 1.0

Item {
    visible: true
    width: parent.width
    height: 350

    property alias serverIP: serverIPField.text
    property alias port: portField.text

    NetworkConfigController {
        id: configController
    }

    Rectangle {
        anchors.fill: parent
        color: "white"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20

            Text {
                text: "NETWORK CONFIGURATION\n(TCP/UDP)"
                font.pointSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            RowLayout {
                spacing: 10

                Label {
                    text: "server IP"
                    font.pointSize: 14
                    verticalAlignment: Label.AlignVCenter
                }
                TextField {
                    id: serverIPField
                    width: 200
                    text: configController.serverIP
                    onTextChanged: configController.setServerIP(text)
                }
            }

            RowLayout {
                spacing: 10

                Label {
                    text: "Port"
                    font.pointSize: 14
                    verticalAlignment: Label.AlignVCenter
                }
                TextField {
                    id: portField
                    width: 100
                    text: configController.port
                    onTextChanged: configController.setPort(parseInt(text))
                }
            }

            // New RowLayout for inline buttons
            RowLayout {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    text: "Save"
                    Layout.preferredWidth: Style.preferredWidth
                    Layout.preferredHeight: Style.preferredHeigth
                    background: Rectangle {
                        color: Style.primary
                        radius: Style.borderRadiusField
                        border.width: 1
                        border.color: Style.borderLineSecondary
                    }
                    onClicked: configController.saveConfig()
                }

                Button {
                    text: "Load"
                    Layout.preferredWidth: Style.preferredWidth
                    Layout.preferredHeight: Style.preferredHeigth
                    background: Rectangle {
                        color: Style.primary
                        radius: Style.borderRadiusField
                        border.width: 1
                        border.color: Style.borderLineSecondary
                    }
                    onClicked: configController.loadConfig()
                }
            }
        }
    }
}
