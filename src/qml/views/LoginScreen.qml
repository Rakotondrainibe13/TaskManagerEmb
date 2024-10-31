import QtQuick 2.9
import QtQuick.Controls 2.9
import QtQuick.Layouts 1.3
import QtQuick.Shapes 1.15
import assets 1.0

Item {
    anchors.fill: parent
    Connections {
        target: mainController.formValidator
        onValidatePasswordFailed: {
            errorPasswordField.text = errorMessage;
            errorPasswordField.visible = true;
            errorAuthentificationField.visible = false;
        }

        onValidateEmailFailed: {
            errorEmailField.text = errorMessage;
            errorEmailField.visible = true;
            errorAuthentificationField.visible = false;
        }
    }
    Connections {
        target: mainController.securityEvent
        onSecurityEvent: {
            errorAuthentificationField.text = event;
            errorAuthentificationField.visible = true;
            errorEmailField.visible = false;
            errorPasswordField.visible = false;

        }
    }

    Rectangle {
        anchors.fill: parent
        ColumnLayout {
            anchors {
                verticalCenter: parent.verticalCenter
                verticalCenterOffset: -50
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: -100
            }

            spacing: 30

            Text {
                text: "Authentification"
                Layout.alignment: Qt.AlignHCenter
                font {
                    family: Style.fontHelvetica
                    pixelSize: 20
                    bold: true
                }
            }

            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 10

                Text {
                    text: "Email"
                    font {
                        family: Style.fontHelvetica
                        pixelSize: Style.sizeTextNormale
                    }
                }

                TextField {
                    id: usernameField
                    placeholderText: "Email"
                    text: "user2@example.com"
                    Layout.preferredWidth: 250
                    Layout.preferredHeight: 30
                    padding: 5
                    background: Rectangle {
                        radius: Style.borderRadiusField
                        color: "#E8F0FE"
                        border.color: Style.borderLine
                    }
                }

                Text {
                   id: errorEmailField
                   color: Style.danger
                   visible: false
                }

                Text {
                    text: "Password"
                    font {
                        family: Style.fontHelvetica
                        pixelSize: Style.sizeTextNormale
                    }
                }

                TextField {
                    id: passwordField
                    placeholderText: "Password"
                    text: "password"
                    echoMode: TextInput.Password
                    Layout.preferredWidth: 250
                    Layout.preferredHeight: 30
                    padding: 5
                    background: Rectangle {
                        radius: Style.borderRadiusField
                        color: "#E8F0FE"
                        border.color: Style.borderLine
                    }
                }

                Text {
                   id: errorPasswordField
                   color: "red"
                   visible: false
                }

                Text {
                    id :errorAuthentificationField
                    color: "red"
                    font.pixelSize: 12
                    Layout.alignment: Qt.AlignHCenter
                }


                Button {
                    id: loginButton
                    text: "Sign in"
                    Layout.alignment: Qt.AlignCenter
                    Layout.preferredWidth: Style.preferredWidth
                    Layout.preferredHeight: Style.preferredHeigth
                    // Layout.preferredHeight: 30
                    contentItem: Text {
                        text: loginButton.text
                        font.pixelSize: Style.sizeTextNormale
                        font.bold: true
                        color: Style.textColorBouton
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    background: Rectangle {
                        id: buttonBackground
                        color: Style.primary
                        border.width: 1
                        border.color: Style.borderLineSecondary
                        radius: Style.borderRadiusField
                    }

                    onClicked: {
                        mainController.login(usernameField.text, passwordField.text)
                    }
                }
            }
        }
    }
}
