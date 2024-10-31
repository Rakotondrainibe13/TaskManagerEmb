import QtQuick 2.9
import QtQuick.Layouts 1.3
import assets 1.0

Item {
    property alias titre: titre.text
    property alias data_value: data_value.text

    Column{
        spacing: 10
        width: parent.width
        // Status
        RowLayout{
            width: parent.width
            Layout.alignment: Qt.AlignVCenter
            Text {
                id: titre
                leftPadding: 20
                topPadding: 20
                Layout.alignment: Qt.AlignLeft
                font {
                    family: Style.fontHelvetica
                    pixelSize: 12
                    bold: true
                }
            }

            Text {
                id: data_value
                topPadding: 20
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: 20
                font.family: Style.fontHelvetica
            }
        }

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.8
            height: 1
            color: "black"
        }
    }


}
