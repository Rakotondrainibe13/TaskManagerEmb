import QtQuick 2.14
import QtQuick.Controls 2.14
import assets 1.0
import QtQuick.Layouts 1.15

Column {
    spacing: 10
    property string m_label: "default label"
    property string m_placeHolder: "default placeholder"
    property string m_inputText: ""
    property string m_error: "default error message"
    
    property real m_height: Style.heigthField
    property real m_width: 100
    property bool m_showError: false
    
    property int m_labelSize: Style.sizeTextNormale
    property int m_inputSize: Style.sizeTextNormale
    

    Text {
        id: inputLabel
        text: qsTr(m_label)
        font.pixelSize: m_labelSize
        font.weight: 525
    }

        
    TextField {
        id: inputField
        text: qsTr(m_inputText)
        placeholderText: m_placeHolder
        height: m_height
        width: m_width
        font.pixelSize: m_inputSize
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        onTextChanged: m_inputText = text 
    }
    

    Text {
        id: inputError
        color: "#FF0000"
        text: qsTr(m_error)
        visible: m_showError
        // font.weight: Font.Bold
    }
}
