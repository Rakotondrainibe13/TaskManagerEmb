import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0
import QtQuick.Layouts 1.3
import components 1.0

Item {
    property int id
    property var taskDetails

    // COMPONENT LOADER
    Component.onCompleted: {
        var task = mainController.getTaskPtrById(id);
        if (task) {
            taskDetails = task;
            console.log("task found with ID: " + taskDetails.taskId);
        } else {
            console.log("task not found with ID: " + id);
        }
    }

    Rectangle {
        id: idCreateTask
        height: parent.height
        width: parent.width
        anchors {
            fill: parent
            left: parent.left
            margins: 10
        }
        color: Style.backgroundSecondary

        // TITRE DE LA PAGE
        Rectangle {
            id: titlePage
            width: idCreateTask.width
            height: 100
            anchors {
                top: idCreateTask.top
                left: idCreateTask.left
            }
            color: "#ffffff"
            border.color: Style.textColor

            RowLayout{
                anchors.fill: parent
                Text {
                    text: "Titre: " + taskDetails.title
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                    Layout.leftMargin: 20
                    font {
                        family: Style.fontHelvetica
                        pixelSize: 24
                        bold: true
                    }
                }

                Button{
                    height: 75
                    padding: 10

                    background: Rectangle{
                         radius: 10
                         border.color: Style.textColor
                    }
                    icon.source: Qt.resolvedUrl("qrc:/assets/edit.png")
                    text: "Edit"
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                    Layout.rightMargin: 50
                    onClicked: {
                        mainController.ui_navigationController.goEditTaskScreen(taskDetails.taskId)
                    }
                }
            }
        }

        // DETAIL DE LA PAGE
        Rectangle {
            id: collumnPage
            width: idCreateTask.width
            anchors.top: titlePage.bottom
            anchors.topMargin: 20


            GridLayout{
                id: gridDetail
                columns: 2
                rows: 2
                anchors.fill: parent


                // DESCRIPTION DE LA TACHE
                Rectangle{
                    id: descriptionTask
                    Layout.preferredHeight: 300
                    Layout.preferredWidth: parent.width * 0.65
                    border.color: Style.textColor
                    color: "#ffffff"

                    ScrollView{

                        width: parent.width
                        height: parent.height
                        clip : true
                        padding: 20

                        Column {
                            width: parent.width  // Ensure the column takes the width of the scroll view
                            // padding: 20

                            Text {
                                width: parent.width
                                text: "Description:"
                                font {
                                    family: Style.fontHelvetica
                                    pixelSize: 16
                                    bold: true
                                }
                                bottomPadding: 30
                            }


                            Text {
                                 width: parent.width
                                text: taskDetails.description
                                font.family: Style.fontHelvetica
                                wrapMode: Text.WordWrap
                            }
                        }
                    }
                }

                // LES DATES CONCERNANTS LA TACHE
                Rectangle{
                    id: dateTask
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.width * 0.3

                    Column{
                        width: dateTask.width

                        // TYPE
                        AboutTask{
                            height: 50
                            anchors{
                                left: parent.left
                                right: parent.right
                            }

                            titre: "Type"
                            data_value: taskDetails.taskType
                        }

                        // Status
                        AboutTask{
                            height: 50
                            anchors{
                                left: parent.left
                                right: parent.right
                            }

                            titre: "Status"
                            data_value: taskDetails.status
                        }

                        // PRIOTITY
                        AboutTask{
                            height: 50
                            anchors{
                                left: parent.left
                                right: parent.right
                            }

                            titre: "Priority"
                            data_value: taskDetails.priorityString
                        }

                        // Start date
                        AboutTask{
                            height: 50
                            anchors{
                                left: parent.left
                                right: parent.right
                            }

                            titre: "Start date"
                            data_value: Qt.formatDateTime(taskDetails.dateTask, "dd/MM/yyyy hh:mm")
                        }


                        // Date update
                        AboutTask{
                            height: 50
                            anchors{
                                left: parent.left
                                right: parent.right
                            }

                            titre: "Due date"
                            data_value: Qt.formatDateTime(taskDetails.duedate, "dd/MM/yyyy hh:mm")
                        }
                    }
                }


                // LES PERSONNES ASSIGNES A LA TACHE
                Rectangle{
                    id: users
                    Layout.preferredHeight: 130
                    Layout.preferredWidth: parent.width * 0.65
                    Layout.alignment: Qt.AlignBottom
                    // border.color: Style.textColor
                    // color: "#ffffff"

                    Column {
                        width: parent.width
                        Text {
                            id: title
                            leftPadding: 20
                            topPadding: 20
                            width: parent.width
                            text: "Users assigned :"
                            font {
                                family: Style.fontHelvetica
                                pixelSize: 16
                                bold: true
                            }
                        }

                        ListView {
                            anchors{
                                top: title.bottom
                                topMargin: 15
                                left: parent.left
                                leftMargin: 20
                            }
                            width: parent.width
                            height: users.height

                            model: mainController.getUsersAssignedTask(taskDetails.taskId)
                            delegate: Item {
                                width: parent.width
                                height: 20

                                RowLayout {
                                    spacing: 20

                                    Rectangle {
                                        width: 10
                                        height: 10
                                        color: "blue"  // Dot color
                                        radius: 5  // Makes the rectangle a circle
                                    }

                                    Text {
                                        text: modelData.username
                                        font.family: Style.fontHelvetica
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle{
                    Layout.topMargin: 20
                    Layout.alignment: Qt.AlignTop
                    ColumnLayout{
                        spacing: 30

                        Button{
                            height: 75
                            padding: 10
                            background: Rectangle{
                                 radius: 10
                                 // color: Style.secondary
                                 border.color: Style.textColor
                            }
                            icon.source: Qt.resolvedUrl("qrc:/assets/check.png")

                            text: "Add to planning"
                        }
                        Button{
                            height: 75
                            padding: 10
                            background: Rectangle{
                                 radius: 10
                                 border.color: Style.textColor
                            }
                            icon.source: Qt.resolvedUrl("qrc:/assets/delete.png")
                            text: "Delete"
                            onClicked: {
                                confirmationDialog.open()
                            }
                        }
                    }
                }
            }
        }
    }
    // DIALOG DE SUPPRESSION
    Dialog {
        id: confirmationDialog
        title: "Deleting task"
        modal: true
        anchors.centerIn: parent
        padding: 20
        width: 600
        height: 200

        background: Rectangle {
            color: Style.backgroundSecondary
            radius: 10
        }

        opacity: 1

        ColumnLayout {
            spacing: 20
            anchors.fill: parent

            RowLayout {
                Layout.alignment: Qt.AlignCenter
                spacing: 8

                Image {
                    Layout.preferredWidth: 24
                    Layout.preferredHeight: 24
                    source: "qrc:/assets/delete.png" // Replace with your actual image path
                    fillMode: Image.PreserveAspectFit
                }

                Text {
                    text: qsTr("Delete task : '") + taskDetails.title + qsTr("' and all its subtask content?")
                    font.pixelSize: 16
                    font.weight: Font.Bold
                    color: Style.textColor
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 20

                Button {
                    text: "Yes"
                    flat: false

                    onClicked: {
                        mainController.deleteTask(taskDetails.taskId);
                        mainController.ui_navigationController.goListTaskScreen()
                    }
                }

                Button {
                    text: "Cancel"
                    flat: true

                    onClicked: {
                        confirmationDialog.close(); // Simply close the dialog without any action
                    }
                }
            }
        }
    }
}
