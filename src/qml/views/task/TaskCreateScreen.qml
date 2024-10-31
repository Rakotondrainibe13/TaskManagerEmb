import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0
import QtQuick.Dialogs
import components 1.0
// import singleton.FormValidator 1.0
Item {
    id: root

    Connections {
        target: mainController.formValidator
        onValidateTitleFailed: {
            titleField.m_error = errorMessage;
            titleField.m_showError = true;
        }
        onValidateDescriptionFailed: {
            descriptionField.m_error = errorMessage;
            descriptionField.m_showError = true;
        }
        onValidateDueDateFailed: {
            dueDate.m_error = errorMessage;
            dueDate.m_showError = true;
        }
    }


    Connections {
        target: mainController.ui_taskManager

        onMaxTaskNumberReached: function(message) {
            subscriptionAskingDialog.informativeText = message;
            subscriptionAskingDialog.open();
        }
    }

    Connections{
        target: mainController
        onUi_taskCreated: {         
            titleField.m_inputText = ""
            priority.m_current = 0
            typeTask.m_current = 0
            
            var now = new Date();                  
            now.setDate(now.getDate() + 1);        
            dueDate.m_inputText = Qt.formatDateTime(now, "dd/MM/yyyy HH:mm") 
            descriptionField.m_inputText = ""
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
            width: parent.width / 2
            anchors.top: titlePage.bottom
            anchors.topMargin: 20

            
            Column {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 0.8
                spacing: 10


                
                InputText{
                    id: titleField
                    m_label: qsTr("Task Title")
                    m_placeHolder: qsTr("Enter task title")
                    m_width: parent.width
                    m_inputText: qsTr("Task 1")
                    // m_showError: true
                }

                // // PRIORITY OF THE TASK

                MyComboBox{
                    id: priority
                    m_label: qsTr("Priority")
                    m_list: ListModel {
                        ListElement { text: "Low" }
                        ListElement { text: "Medium" }
                        ListElement { text: "High" }
                    }
                }

                // TYPE OF THE TASK

                MyComboBox{
                    id: typeTask
                    m_label: qsTr("Task type")
                    m_list: ListModel {
                        ListElement { text: "Simple" }
                        ListElement { text: "Recurring" }
                        ListElement { text: "Project" }
                    }
                }

                InputText{
                    id: dueDate
                    m_label: qsTr("Due Date")
                    m_placeHolder: qsTr("dd/MM/yyyy HH:mm")
                    m_width: 150
                    m_inputText:  {
                        var now = new Date();                  // Crée un objet Date pour maintenant
                        now.setDate(now.getDate() + 1);        // Ajoute un jour à la date actuelle
                        Qt.formatDateTime(now, "dd/MM/yyyy HH:mm")  // Formate la nouvelle date et heure
                     }

                }

                // Text {
                //    id: errorDueDateField
                //    color: "red"
                //    visible: false
                // }

                InputText{
                    id: descriptionField
                    m_label: qsTr("Task Description")
                    m_placeHolder: qsTr("Enter task title")
                    m_width: parent.width
                    m_height: 90
                    m_inputText: qsTr("Cette task est conçu pour le test du Task Manager")
                    m_inputSize: 12

                }


            }
        }

        Rectangle {
            width: parent.width
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

                Button {
                    text: qsTr("Reset")
                    width: Style.preferredWidth
                    height: Style.preferredHeight
                    anchors.leftMargin: 10
                    background: Rectangle {
                        id: buttonBackground
                        color: Style.primary
                        radius: Style.borderRadiusField
                    }
                    onClicked: {
                        mainController.ui_navigationController.goCreateTaskScreen()
                    }
                }

                Button {
                    text: qsTr("Create")
                    width: Style.preferredWidth
                    background: Rectangle {
                        color: Style.primary
                        radius: Style.borderRadiusField
                    }
                    onClicked: {
                        confirmationDialog.open()
                    }
                }

                MessageDialog {
                    id: confirmationDialog
                    text: "Confirmation"
                    informativeText: "Do you really create "+ titleField.m_inputText + " ?"
                    buttons: MessageDialog.Ok | MessageDialog.Cancel

                    onAccepted: {
                        dueDate.m_showError = false;
                        titleField.m_showError = false;
                        descriptionField.m_showError = false;
                        mainController.createTaskAsync(titleField.m_inputText, descriptionField.m_inputText, (priority.m_current + 1) , dueDate.m_inputText, typeTask.m_current)
                    }
                }

                MessageDialog {
                    id: subscriptionAskingDialog
                    text: "The limit of the free trial has been reached!"
                    informativeText: ""
                    buttons: MessageDialog.Ok | MessageDialog.Cancel

                    onAccepted: {
                        mainController.ui_navigationController.goSubscriptionStateScreen()
                    }
                }
            }
        }
    }
}
