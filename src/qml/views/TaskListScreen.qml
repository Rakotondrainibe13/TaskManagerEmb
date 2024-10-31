import QtQuick 2.9
import assets 1.0
import QtQuick.Controls 2.15
import Qt.labs.settings 1.0
import QtQuick.Layouts 1.3
import components 1.0

Item {
    Rectangle {
        id: idParentTask
        width: parent.width
        anchors {
            fill: parent
            left: parent.left
        }
        color: Style.colourBackground

        // Filter
        RowLayout {
            id: idFiltre
            width: 400
            height: 60
            spacing: 5  // Réduction de l'espacement entre les éléments
            anchors {
                top: parent.top
                left: parent.left
                leftMargin: 20
                topMargin: 10
            }


            Rectangle {
                width: 150
                height: Style.heigthField
                color: Style.white
                border.color: Style.borderLineSecondary
                radius: Style.borderRadiusField

                // Use anchors to make the TextField follow the Rectangle's borders
                TextField {
                    id: filterInput
                    placeholderText: qsTr("Search...")
                    font.pixelSize: Style.sizeTextNormale

                    // Make the TextField fill the Rectangle while respecting padding
                    anchors.fill: parent
                    anchors.margins: 0
                    onTextChanged:{
                        mainController.applyFilter(filterInput.text);
                    }
                }
            }


            ComboBox {
                id: sortDropdown
                model: combo_type
                Layout.preferredWidth: Style.preferredWidth
                Layout.preferredHeight: Style.heigthField
                Layout.alignment: Qt.AlignVCenter
                ListModel {
                    id: combo_type
                    ListElement { text: "No Sorting" }
                    ListElement { text: "Due date Asc" }
                    ListElement { text: "Due date Desc" }
                }
                currentIndex: 0
                onCurrentIndexChanged:{
                    mainController.applySort(sortDropdown.currentIndex);
                }
            }

            // Button {
            //     id: searchButton
            //     Layout.preferredWidth: 40
            //     Layout.preferredHeight: Style.preferredHeigth
            //     Layout.alignment: Qt.AlignVCenter
            //     background: Rectangle {
            //         // color: Style.primary
            //         radius: Style.borderRadiusField
            //     }
            //     contentItem: RowLayout {
            //         anchors.centerIn: parent
            //         Image {
            //             source: Style.iconSearchBase64
            //             width: 20
            //             height: 20
            //             fillMode: Image.PreserveAspectFit
            //             anchors.verticalCenter: parent.verticalCenter
            //             anchors.horizontalCenter: parent.horizontalCenter
            //         }
            //     }
            //     onClicked: {
            //         // Ajouter l'action de recherche ici
            //     }
            // }
        }




        // Kanban
        Rectangle {
            id: idListeTask
            width: parent.width
            height: parent.height - 135 // Ajustement pour faire de la place aux boutons
            anchors {
                left: parent.left
                top: idFiltre.bottom
                margins: 20
                // rightMargin: 20
            }
            color: Style.colourBackground

            Rectangle {
                id: titlePage
                width: idListeTask.width
                height: idListeTask.height
                anchors {
                    top: idListeTask.top
                    left: idListeTask.left
                }

                Rectangle {
                    id: idPending
                    width: (parent.width / 3) - 4
                    height: parent.height
                    border.color: Style.borderLineSecondary
                    border.width: 1
                    Column {
                        anchors.fill: parent
                        spacing: 20
                        Text {
                            id: idTextPending
                            text: "Pending"
                            font.pixelSize: Style.sizeTextTitle
                            topPadding: 10
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                            }
                        }

                        Repeater {
                            model: mainController.tasks

                            TaskCard {
                                visible: modelData.status === 0 ? true : false
                                title: modelData.title
                                taskId:modelData.taskId
                                dateTask: Qt.formatDateTime(modelData.dateTask, "dddd dd MMMM yyyy hh:mm:ss")
                            }
                        }
                    }
                }
                Rectangle {
                    id: idProgress
                    width: (parent.width / 3) - 4
                    height: parent.height
                    border.color: Style.borderLineSecondary
                    border.width: 1
                    anchors {
                        left: idPending.right
                        margins: 6
                    }
                    Column {
                        anchors.fill: parent
                        spacing: 20
                        Text {
                            text: "In Progress"
                            font.pixelSize: Style.sizeTextTitle
                            topPadding: 10
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                            }
                        }

                        Repeater {
                            model: mainController.tasks

                            TaskCard {
                                visible: modelData.status === 1 ? true : false
                                title: modelData.title
                                taskId:modelData.taskId
                                dateTask: Qt.formatDateTime(modelData.dateTask, "dddd dd MMMM yyyy hh:mm:ss")
                            }
                        }
                    }
                }
                Rectangle {
                    id: idCompleted
                    width: (parent.width / 3) - 4
                    height: parent.height
                    border.color: Style.borderLineSecondary
                    border.width: 1
                    anchors {
                        margins: 6
                        left: idProgress.right
                    }
                    Column {
                        anchors.fill: parent
                        spacing: 20
                        Text {
                            text: "Completed"
                            font.pixelSize: Style.sizeTextTitle
                            topPadding: 10
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                            }
                        }

                        Repeater {
                            model: mainController.tasks
                            TaskCard {
                                visible: modelData.status === 2 ? true : false
                                title: modelData.title
                                taskId:modelData.taskId
                                dateTask: Qt.formatDateTime(modelData.dateTask, "dddd dd MMMM yyyy hh:mm:ss")
                            }
                        }
                    }
                }
            }
        }

        RowLayout {
            id: paginationControls
            width: parent.width
            anchors {
                bottom: parent.bottom
                bottomMargin: 10
                top: idListeTask.bottom
                topMargin: 3
                left: parent.left
                leftMargin: 20
                right: parent.right
                rightMargin: 20
            }

            Button {
                id: nextButton
                Layout.preferredWidth: Style.preferredWidth
                Layout.preferredHeight: Style.preferredHeigth
                Layout.alignment: Qt.AlignCenter
                font.pixelSize: Style.sizeTextNormale
                background: Rectangle {
                    color: Style.primary
                    radius: Style.borderRadiusField
                    border.width: 1
                    border.color: Style.borderLineSecondary
                }
                onClicked: {
                    if(mainController.hasPrevious){
                        mainController.previousPage();
                    }
                }
                visible: mainController.hasPrevious
                contentItem: Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        Text {
                            text: "Preview"
                            font.pixelSize: Style.sizeTextNormale
                            color: Style.textColorBouton
                            anchors.centerIn: parent
                        }
                }
            }

            Item {
                width: parent.width - 240
                height: 40
            }

            Button {
                id: prevButton
                Layout.preferredWidth: Style.preferredWidth
                Layout.preferredHeight: Style.preferredHeigth
                Layout.alignment: Qt.AlignCenter
                font.pixelSize: Style.sizeTextNormale
                background: Rectangle {
                    color: Style.primary
                    radius: Style.borderRadiusField
                    border.width: 1
                    border.color: Style.borderLineSecondary
                }
                onClicked: {
                    if(mainController.hasNext){
                        mainController.nextPage();
                    }
                }
                visible:mainController.hasNext
                contentItem: Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        Text {
                            text: "Next"
                            font.pixelSize: Style.sizeTextNormale
                            color: Style.textColorBouton
                            anchors.centerIn: parent
                        }
                    }
            }
        }
    }
}
