import QtQuick 2.14
import QtQuick.Controls 2.14
import assets 1.0
Column{
    spacing: 10
    property string m_label: "default combo label"
    property ListModel m_list: ListModel {
            ListElement { text: "combo 1" }
            ListElement { text: "combo 2" }
            ListElement { text: "combo 3" }
        }
    property int  m_current: 0
    
    property int m_labelSize: Style.sizeTextNormale

    Text {
        id: boxLabel
        text: qsTr(m_label)
        font.pixelSize: m_labelSize
        font.weight: 525
    }

    ComboBox {
        id: myCombo
        model: m_list
        height: Style.heigthField

        currentIndex: m_current

        onCurrentIndexChanged: m_current = currentIndex
    }
}