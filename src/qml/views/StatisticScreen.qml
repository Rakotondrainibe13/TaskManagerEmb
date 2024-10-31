import QtQuick 2.15
import QtQuick.Controls 2.15
import QtCharts 2.15
import QtQuick.Layouts 1.15
Item {

    ScrollView {
        width: parent.width
        height: parent.height

        Column {
            width: parent.width
            spacing: 20

            // Titre
            Rectangle {
                width: parent.width
                height: 60
                color: "white"
                border.width: 0
                Text {
                    text: "Reports and Statistics"
                    anchors.centerIn: parent
                    font.pixelSize: 24
                    font.bold: true
                }
            }

            // Aperçu des tâches
            Rectangle {
                width: parent.width
                height: 100
                color: "white"
                border.width: 0
                radius: 5

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 20  // Add spacing between the two columns

                    // Column for "Aperçu des Tâches"
                    ColumnLayout {
                        Layout.fillWidth: true  // Ensures both columns take equal width
                        spacing: 5

                        Text {
                            text: "Tasks Overview"
                            font.pixelSize: 14
                            font.bold: true
                        }

                        Text {
                            text: mainController.report.totalTasks
                            font.pixelSize: 36
                            font.bold: true
                        }

                        Text {
                            text: "Total tasks"
                            color: "gray"
                        }
                    }

                    // Column for "Tâches Complétées"
                    ColumnLayout {
                        Layout.fillWidth: true  // Ensures both columns take equal width
                        spacing: 5

                        Text {
                            text: "Tasks Completed"
                            font.pixelSize: 14
                            font.bold: true
                        }

                        Text {
                            text: mainController.report.completedTasks
                            font.pixelSize: 36
                            font.bold: true
                        }

                        Text {
                            text: mainController.report.completionRate + "%"
                            color: "gray"
                        }
                    }
                }

            }

            // Graphique Pie
            ChartView {
                width: parent.width
                height: 300
                title: "Task Status"
                legend.alignment: Qt.AlignBottom
                antialiasing: true

                PieSeries {
                    PieSlice {label: "To do"
                        value: mainController.statisticmodel.todoValue
                    }
                    PieSlice {
                        label: "In progress"
                        value: mainController.statisticmodel.inProgressValue
                    }
                    PieSlice {
                        label: "Finished"
                        value: mainController.statisticmodel.completedValue
                    }
                }
            }

            // Graphique Bar
            ChartView {
                width: parent.width
                height: 300
                title: "Task activity (per day)"
                legend.alignment: Qt.AlignBottom
                antialiasing: true

                BarSeries {
                    BarSet {
                        label: "Tasks Completed"
                        values: ["2","2","5","4","5","6","1"]
                    }
                }

                BarCategoryAxis {
                    categories: ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
                }
            }

            ColumnLayout {
                width: parent.width
                spacing: 20

                // Tâches en Retard Section
                Rectangle {
                    width: parent.width
                    height: 200
                    color: "white"
                    border.color: "#d3d3d3"
                    radius: 5
                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 20

                        // Section Title
                        RowLayout {
                            spacing: 10
                            Image {
                                source: "qrc:/icons/warning.png" // Replace with appropriate icon
                                width: 24
                                height: 24
                            }
                            Text {
                                text: "Late Tasks"
                                font.pixelSize: 18
                                font.bold: true
                            }
                        }

                        // Number of delayed tasks
                        Text {
                            text: mainController.statisticmodel.delayedValue
                            color: "red"
                            font.pixelSize: 48
                            font.bold: true
                        }

                        // List of delayed tasks
                        Column {
                            spacing: 5
                            Repeater {
                                model: mainController.statisticmodel.delayedTasks
                                delegate: Text {
                                    text: modelData
                                    color: "gray"
                                }
                            }
                        }
                    }
                }

                // Actions Rapides Section
                Rectangle {
                    width: parent.width
                    height: 80
                    color: "white"
                    border.width: 0
                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 10

                        // Quick Action Buttons
                        Button {
                            text: "Generate a PDF report"
                            background: Rectangle {
                                color: "#008CFF"
                                radius: 5
                            }
                            font.pixelSize: 16
                            font.bold: true
                            contentItem: Text {
                                text: "Generate a PDF report"
                                color: "white"
                            }
                        }

                        Button {
                            text: "Export CSV data"
                            background: Rectangle {
                                color: "#00C853"
                                radius: 5
                            }
                            font.pixelSize: 16
                            font.bold: true
                            contentItem: Text {
                                text: "Export CSV data"
                                color: "white"
                            }
                        }

                        Button {
                            text: "Configure alerts"
                            background: Rectangle {
                                color: "#8E24AA"
                                radius: 5
                            }
                            font.pixelSize: 16
                            font.bold: true
                            contentItem: Text {
                                text: "Configure alerts"
                                color: "white"
                            }
                        }
                    }
                }
            }
        }
    }
}
