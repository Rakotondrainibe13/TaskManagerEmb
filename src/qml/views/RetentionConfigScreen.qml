import QtQuick 2.9
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Controllers 1.0
import assets 1.0
import QtQuick.Dialogs

Item {
    visible: true
    width: parent.width
    height: 350
    Connections {
        target: mainController.synchManager
        onRetentionConfigCompleted: {
            confirmationDialog.informativeText = result;
            confirmationDialog.text = response;
            confirmationDialog.open();
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "white"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 20

            Text {
                text: "RETENTION CONFIGURATION"
                font.pointSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            RowLayout {
                spacing: 30

                Label {
                    text: "Month"
                    font.pointSize: 14
                    verticalAlignment: Label.AlignVCenter
                }
                TextField {
                    id: mois
                    width: 100
                    inputMethodHints: Qt.ImhDigitsOnly
                    text: "0"
                }

                Label {
                    text: "Day"
                    font.pointSize: 14
                    verticalAlignment: Label.AlignVCenter
                }
                TextField {
                    id: jour
                    width: 100
                    inputMethodHints: Qt.ImhDigitsOnly
                    text: "0"
                }
            }

            RowLayout {
                spacing: 30

                Label {
                    text: "Hour"
                    font.pointSize: 14
                    verticalAlignment: Label.AlignVCenter
                }
                TextField {
                    id: heure
                    width: 100
                    inputMethodHints: Qt.ImhDigitsOnly
                    text: "0"
                }

                Label {
                    text: "Minute"
                    font.pointSize: 14
                    verticalAlignment: Label.AlignVCenter
                }
                TextField {
                    id: minute
                    width: 100
                    inputMethodHints: Qt.ImhDigitsOnly
                    text: "0"
                }
            }

            RowLayout {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    text: "Save"
                    Layout.preferredWidth: tyle.preferredWidth
                    Layout.preferredHeight: Style.preferredHeigth
                    background: Rectangle {
                        color: Style.primary
                        radius: Style.borderRadiusField 
                        border.width: 1
                        border.color: Style.borderLineSecondary 
                    }
                    onClicked: {
                        mainController.updateRetentionConfig(mois.text,jour.text,heure.text,minute.text);
                    }
                }
            }

            MessageDialog {
                id: confirmationDialog
                buttons: MessageDialog.Ok
            }
        }
    }
}
