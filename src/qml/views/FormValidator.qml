import QtQuick 2.15
import QtQuick.Controls 2.15
import com.mycompany.formvalidator 1.0
import Qt.labs.settings 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Task Manager")

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#f0f0f0"

        Column {
            spacing: 10
            anchors.centerIn: parent
            width: parent.width * 0.8

            TextField {
                id: emailField
                placeholderText: qsTr("Enter your email")
                width: parent.width
            }

            TextField {
                id: passwordField
                placeholderText: qsTr("Enter your password")
                echoMode: TextInput.Password
                width: parent.width
            }

            TextField {
                id: titleField
                placeholderText: qsTr("Enter task title")
                width: parent.width
            }

            TextField {
                id: descriptionField
                placeholderText: qsTr("Enter task description")
                width: parent.width
                height: 100
            }

            TextField {
                id: textDate
                x: 10
                y: 42
                width: 175
                height: 33
                placeholderText: qsTr("dd/MM:yyyy")
                text:Qt.formatDate(cal.selectedDate, "dd/MM/yyyy")
                font.pointSize: 12
            }

            Button {
                text: qsTr("Validate")
                width: parent.width
                onClicked: {
                    var dateString = textDate.text;

                    var someDateTest = Date.fromLocaleString(Qt.locale(), dateString, "dd/MM/yyyy")
                    var dateObject = someDateTest.getDate()
                    console.log(emailField.text);
                    console.log(emailField.text);
                    console.log(emailField.text);
                    console.log(emailField.text);

                    if (FormValidator.validateEmail(emailField.text) &&
                        FormValidator.validatePassword(passwordField.text) &&
                        FormValidator.validateTaskTitle(titleField.text) &&
                        FormValidator.validateTaskDescription(descriptionField.text) /*&&
                        formvalidator.validateTaskDueDate(someDateTest)*/
                        ) {
                        console.log("Validation passed")
                    } else {
                        console.log("Validation failed")
                    }
                }
            }
        }
    }
}
