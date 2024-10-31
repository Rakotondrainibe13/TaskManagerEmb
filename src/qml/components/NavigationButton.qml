import QtQuick 2.9
import assets 1.0

Item {
    property alias iconCharacter: textIcon.text
    property alias description: textDescription.text
    property color hoverColour: Style.backgroundSecondary

    signal navigationButtonClicked()

    width: parent.width
    height: 50

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.backgroundPrincipale

        Row {
            Text {
                id: textIcon
                width: 50
                height: 50
                font {
                    family: "Helvetica"
                    pixelSize: 24
                }
                color: Style.textColor
                text: "\uf11a"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                id: textDescription
                width: 50
                height: 50
                color: Style.textColor
                text: "SET ME!!"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 13
            }
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: navigationButtonClicked()
        }

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: Style.white
                }
            }
        ]
    }
}
