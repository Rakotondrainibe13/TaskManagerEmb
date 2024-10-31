import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0
import QtQuick.Layouts 1.3
import components 1.0

Item {
    property int id
    property var taskDetails
    property var assignedUsers
    property var nonAssignedUsers
    property int userToUnassigned

    // COMPONENT LOADER
    Component.onCompleted: {
        var task = mainController.getTaskPtrById(id)
        if (task) {
            taskDetails = task
            assignedUsers = mainController.getUsersAssignedTask(taskDetails.taskId)
            nonAssignedUsers = mainController.getUsersNotAssignedTask(taskDetails.taskId)
            console.log("task found with ID: " + taskDetails.taskId);
        } else {
            console.log("task not found with ID: " + id);
        }
    }

    Connections{
        target: mainController
        function onUpdateUsersAssignment(){
            assignedUsers = mainController.getUsersAssignedTask(taskDetails.taskId)
            nonAssignedUsers = mainController.getUsersNotAssignedTask(taskDetails.taskId)
        }
    }

    Connections {
           target: mainController
           onTaskUpdated: {
               modificationNotification.open()
           }
       }

    Rectangle {
        id: idUpdateTask
        height: parent.height
        width: parent.width
        anchors {
            fill: parent
            left: parent.left
            margins: 10
        }
        color: Style.backgroundSecondary

        // PAGE TITLE
        Rectangle {
            id: titlePage
            width: idUpdateTask.width
            height: 100
            anchors {
                top: idUpdateTask.top
                left: idUpdateTask.left
            }
            border.color: Style.textColor

            RowLayout{
                anchors.fill: parent
                Text {
                    text: "Reference Id: " + taskDetails.taskId
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                    Layout.leftMargin: 20
                    font {
                        family: Style.fontHelvetica
                        pixelSize: 24
                        bold: true
                    }
                }
            }
        }

        // PAGE DETAILS
        Rectangle {
            id: collumnPage
            width: idUpdateTask.width
            anchors.top: titlePage.bottom
            anchors.topMargin: 20
            anchors.bottom: idUpdateTask.bottom


            GridLayout{
                id: gridDetail
                columns: 2
                rows: 1
                anchors.fill: parent


                // FORMULAIRE DE SAISIE
                Rectangle{
                    id: descriptionTask
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.width * 0.75
                    Layout.bottomMargin: 30

                    ColumnLayout{
                        id: form
                        width: parent.width
                        height: parent.height
                        spacing: 5

                        // TItre
                        RowLayout{
                            Layout.fillWidth: true
                            Layout.preferredHeight: 50

                            Text{
                                Layout.preferredWidth: descriptionTask.width * 0.3
                                Layout.leftMargin: 30
                                text: "Title : "
                                font {
                                    family: Style.fontHelvetica
                                }
                            }

                            TextField {
                                id: titleField
                                padding: 10
                                Layout.preferredWidth: descriptionTask.width * 0.55
                                text: taskDetails.title
                                height: Style.heigthField
                                placeholderText: qsTr("Enter task title")
                            }
                            Text {
                               id: errorTitleField
                               color: "red"
                               visible: false
                            }
                        }

                        // PRIORITY
                        RowLayout{
                            Layout.fillWidth: true
                            Layout.preferredHeight: 50

                            Text{
                                Layout.preferredWidth: descriptionTask.width * 0.3
                                Layout.leftMargin: 30
                                text: "Priority : "
                                font {
                                    family: Style.fontHelvetica
                                }
                            }

                            ComboBox {
                                id: priority
                                Layout.preferredWidth: descriptionTask.width * 0.55
                                background: Rectangle {
                                    implicitHeight:  Style.heigthField
                                    border.color: Style.textColor
                                }

                                model: combo_priority
                                ListModel {
                                    id: combo_priority
                                    ListElement { text: "Low" }
                                    ListElement { text: "Medium" }
                                    ListElement { text: "High" }
                                }
                                currentIndex: {
                                      switch(taskDetails.priorityString) {
                                          case "Low": return 0;
                                          case "Medium": return 1;
                                          case "High": return 2;
                                          default: return 0; // Default to the first item if no match is found
                                      }
                                  }
                            }
                        }

                        // Due Date
                        RowLayout{
                            Layout.fillWidth: true
                            Layout.preferredHeight: 50

                            Text{
                                Layout.preferredWidth: descriptionTask.width * 0.3
                                Layout.leftMargin: 30
                                text: "Due date : "
                                font {
                                    family: Style.fontHelvetica
                                }
                            }

                            TextField {
                                id: dueDate
                                padding: 10
                                Layout.preferredWidth: descriptionTask.width * 0.55

                                height: Style.heigthField
                                placeholderText: qsTr("dd/MM/yyyy HH:mm")
                                text: {
                                    Qt.formatDateTime(taskDetails.dateTask, "dd/MM/yyyy HH:mm")  // Formate la nouvelle date et heure
                                 }
                            }
                            Text {
                               id: errorDueDateField
                               color: "red"
                               visible: false
                            }
                        }

                        // DESCRIPTION
                        RowLayout{
                            Layout.fillWidth: true
                            Layout.preferredHeight: 50

                            Text{
                                Layout.preferredWidth: descriptionTask.width * 0.3
                                Layout.leftMargin: 30
                                text: "Descripition : "
                                font {
                                    family: Style.fontHelvetica
                                }
                            }

                            TextArea {
                                id: descriptionArea
                                text: taskDetails.description
                                Layout.preferredWidth: descriptionTask.width * 0.55
                                Layout.alignment: Qt.AlignHCenter
                                Layout.preferredHeight: 150
                                wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
                                font.pixelSize: 16
                                padding: 10

                                background: Rectangle {
                                    border.color: "#888"
                                    border.width: 1
                                }
                            }
                            Text {
                               id: errorDescriptionField
                               color: "red"
                               visible: false
                            }
                        }

                        // Bouton update
                        Button{
                            height: 75
                            padding: 10

                            background: Rectangle{
                                 radius: 10
                                 border.color: Style.textColor
                            }
                            icon.source: Qt.resolvedUrl("qrc:/assets/edit.png")
                            text: "Modify"
                            Layout.alignment: Qt.AlignVCenter
                           Layout.leftMargin: 30
                            Layout.topMargin: 30

                            onClicked: {
                                mainController.updateTaskAsync(taskDetails.taskId, titleField.text, descriptionArea.text, (priority.currentIndex + 1), dueDate.text)
                            }
                        }
                    }
                }

                // LES USERS ASSIGNES
                Rectangle{
                    id: userAssigned
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.width * 0.2
                    Layout.bottomMargin: 30
                    border.color: Style.textColor
                    radius: 10

                    ColumnLayout{
                        width: userAssigned.width
                        height: userAssigned.height

                        Text{
                            text: "Users assigned"
                            Layout.alignment: Qt.AlignHCenter
                            padding: 10
                        }

                        Rectangle {
                            Layout.alignment: Qt.AlignHCenter
                            Layout.preferredWidth: userAssigned.width * 0.8
                            height: 1
                            color: "black"

                        }

                        ListView {

                            Layout.fillHeight: true
                            Layout.preferredWidth: userAssigned.width * 0.8

                           model: assignedUsers

                           delegate: Item {
                               height: 50
                               width: userAssigned.width

                               RowLayout {
                                   anchors.fill: parent

                                   Text {
                                       id: titre
                                       text: modelData.username
                                       Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                                       Layout.leftMargin: 10
                                       font {
                                           family: Style.fontHelvetica
                                           pixelSize: 16
                                       }
                                   }


                                    Button {
                                        icon.source: Qt.resolvedUrl("qrc:/assets/delete.png")
                                        Layout.preferredWidth: 30
                                        Layout.preferredHeight: 30
                                        Layout.rightMargin: 10
                                        Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                                        background: Rectangle {
                                            border.color: "transparent" // Make the border transparent
                                        }
                                        onClicked: {
                                            userToUnassigned = modelData.userID
                                            deleteNotification.open()
                                        }
                                    }
                               }
                           }
                       }
                    }
                    Button{
                        anchors{
                            bottom: userAssigned.bottom
                            bottomMargin: 20
                            horizontalCenter: userAssigned.horizontalCenter
                        }

                        padding: 10
                        background: Rectangle{
                             radius: 10
                             border.color: Style.textColor
                        }
                        icon.source: Qt.resolvedUrl("qrc:/assets/plus.png")
                        text: "Add user"
                        onClicked: {
                            userPopup.open()
                        }
                    }
                }
            }
        }
    }

    // DIALOG DE MODIFUCATION
    Dialog {
        id: modificationNotification
        title: "Task modification"
        modal: true
        anchors.centerIn: parent
        padding: 20
        width: 400
        height: 200

        background: Rectangle {
            color: Style.backgroundSecondary
            radius: 10
        }

        opacity: 0

        ColumnLayout {
            spacing: 20
            anchors.fill: parent

            RowLayout {
                Layout.alignment: Qt.AlignCenter
                spacing: 8

                Image {
                    Layout.preferredWidth: 24
                    Layout.preferredHeight: 24
                    source: "qrc:/assets/yes.png" // Replace with your actual image path
                    fillMode: Image.PreserveAspectFit
                }

                Text {
                    text: "Id " + taskDetails.taskId + " modified successfully"
                    font.pixelSize: 16
                    font.weight: Font.Bold
                    color: Style.textColor
                }
            }

            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "OK"
                flat: false

                onClicked: {
                    modificationNotification.close();
                    mainController.ui_navigationController.goDetailTaskScreen(taskDetails.taskId)
                }
            }
        }

        onOpened: opacity = 1
        onClosed: {
            opacity = 0
            modificationNotification.close();
            mainController.ui_navigationController.goDetailTaskScreen(taskDetails.taskId)
        }
    }

    // DELETING USERS ASSIGNMENT POP UP
    Dialog {
        id: deleteNotification
        title: "Unassignment a user"
        modal: true
        anchors.centerIn: parent
        padding: 20
        width: 400
        height: 200

        background: Rectangle {
            color: Style.backgroundSecondary
            radius: 10
        }

        opacity: 0

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
                    text: qsTr("Do you want to unassigned user?")
                    font.pixelSize: 16
                    font.weight: Font.Bold
                    color: Style.textColor
                }
            }

            Button {
                Layout.alignment: Qt.AlignHCenter
                text: "Yes"
                flat: false

                onClicked: {

                    // mainController.ui_navigationController.goEditTaskScreen(taskDetails.taskId)
                    if(mainController.unassignmentTaskUser(taskDetails.taskId, userToUnassigned)){
                        userToUnassigned = 0
                        deleteNotification.close();
                    }

                }
            }
        }

        onOpened: opacity = 1
        onClosed: {
            opacity = 0
            deleteNotification.close();
            // mainController.ui_navigationController.goEditTaskScreen(taskDetails.taskId)
        }
    }


    // ADDING NEW USERS POP UP
    Popup{
            id: userPopup
            width: 300
            height: 400
            modal: true
            focus: true
            anchors.centerIn: parent

            ColumnLayout{
                id: popupTitle
                width: parent.width
                height: parent.height
                spacing: 10

                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 60
                    border.color: "black"
                    border.width: 1
                    radius: 10

                    Text {
                        text: "Assign to users"
                        font.bold: true
                        anchors.centerIn: parent

                    }
                }
                ListView{
                    id: userList
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    property var checkedStates: []

                    Component.onCompleted: {
                        // Initialize the checkedStates array based on the model size
                        for (var i = 0; i < model.length; i++) {
                            checkedStates[i] = false;
                        }
                    }

                    model: nonAssignedUsers

                    delegate: Item{
                        height: 50
                        width: parent.width

                        RowLayout{
                            anchors.fill: parent
                            CheckBox{
                                id: userCheck
                                // Layout.alignment: Qt.AlignVCenter
                                checked: false
                                Layout.preferredWidth: parent.width * 0.2
                                onCheckedChanged: {
                                   // Step 2: Update Checkbox State
                                   userList.checkedStates[index] = checked;
                               }
                            }

                            Text{
                                width: parent * 0.6
                                text: modelData.username
                                Layout.preferredWidth: parent.width * 0.6
                            }
                        }
                    }
                }
            }


            Button{
                id: buttonCours
                padding: 10
                background: Rectangle{
                     radius: 10
                     border.color: Style.textColor
                }
                icon.source: Qt.resolvedUrl("qrc:/assets/plus.png")
                text: "Add user"
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 30

                onClicked: {
                    var selectedUsers = [];
                    var allUsers =  mainController.getUsersNotAssignedTask(taskDetails.taskId)
                    for (var i = 0; i < userList.checkedStates.length; i++) {
                        if (userList.checkedStates[i]) {
                            // Assuming your model items have an 'id' property
                            selectedUsers.push(allUsers[i].userID);
                        }
                    }
                    console.log("Selected USERS: " + selectedUsers.join(", "));
                    var result = mainController.assignmentTaskUserAsync(taskDetails.taskId, selectedUsers);
                    if(result){
                        userPopup.close();
                        // mainController.ui_navigationController.goEditTaskScreen(taskDetails.taskId)
                    }
                }
            }
        }
}
