import QtQuick 2.9
import assets 1.0
import components 1.0
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0

Item {
    Connections {
        target: mainController.formValidator
        onValidateTitleFailed: {
            console.log("Mba tonga eto ve? " + errorMessage);
            errorTitleField.text = errorMessage;
            errorTitleField.visible = true;
        }
        onValidateDescriptionFailed: {
            console.log("Mba tonga eto ve? " + errorMessage);
            errorDescriptionField.text = errorMessage;
            errorDescriptionField.visible = true;
        }
        onValidateDueDateFailed: {
            console.log("Mba tonga eto ve? " + errorMessage);
            errorDueDateField.text = errorMessage;
            errorDueDateField.visible = true;
        }
        onValidateEmailFailed: {
            console.log("malesa ");
        }


    }

    Rectangle {
        id: idCreateTask
        width: parent.width
        anchors {
            fill: parent
            left: parent.left
        }
        color: Style.colourBackground

        Rectangle {
            id: titlePage
            width: idCreateTask.width
            height: 60
            anchors {
                top: idCreateTask.top
                left: idCreateTask.left
            }
            Text {
                text: "New Task"
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 20
                }
                font {
                    family: Style.fontHelvetica
                    pixelSize: 24
                    bold: true
                }
            }
        }

        Rectangle {
            id: collumnPage
            width: idCreateTask.width / 2
            anchors.top: titlePage.bottom
            anchors.topMargin: 20
            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                width: collumnPage.width * 0.8
                spacing: 10

                Text {
                    text: qsTr("Task Title")
                }
                TextField {
                    id: titleField
                    placeholderText: qsTr("Enter task title")
                    width: parent.width
                }

                Text {
                   id: errorTitleField
                   color: "red"
                   visible: false
                }

                Text {
                    text: qsTr("Priority")
                }
                ComboBox {
                    id: priority
                    model: ["P1", "P2", "P3"]
                }

                Text {
                    text: qsTr("Start Date")
                }
                TextField {
                    id: startDate
                    width: 150
                    height: 30
                    placeholderText: qsTr("DD/MM/YYYY")
                    text: Qt.formatDate(cal.selectedDate, "dd/MM/yyyy")
                }
                Text {
                   id: errorStartDateField
                   color: "red"
                   visible: false
                }
                Text {
                    text: qsTr("Due Date")
                }
                TextField {
                    id: dueDate
                    width: 150
                    height: 30
                    placeholderText: qsTr("DD/MM/YYYY")
                    text: Qt.formatDate(cal.selectedDate, "dd/MM/yyyy")
                }
                Text {
                   id: errorDueDateField
                   color: "red"
                   visible: false
                }

                Text {
                    text: qsTr("Task Description")
                }
                TextField {
                    id: descriptionField
                    placeholderText: qsTr("Enter task description")
                    width: parent.width
                    height: 100
                }
                Text {
                   id: errorDescriptionField
                   color: "red"
                   visible: false
                }
            }
        }

        Rectangle {
            width: idCreateTask.width
            height: 60
            anchors {
                bottom: parent.bottom
                right: parent.right
                rightMargin: 20
                bottomMargin: 20
            }

            Row {
                spacing: 10
                anchors.right: parent.right

                // Button {
                //     text: qsTr("Cancel")
                //     width: 100
                //     onClicked: {
                //         console.log("Cancel button clicked")
                //     }
                // }

                Button {
                    text: qsTr("Create")
                    width: 100
                    onClicked: {
                        console.log("Ok button clicked")
                        var newDate = Date.fromLocaleString(Qt.locale(), dueDate.text, "dd/MM/yyyy");
                        mainController.createTask(titleField.text, descriptionField.text, 1, newDate, 0);
                    }
                }
            }
        }
    }
}
