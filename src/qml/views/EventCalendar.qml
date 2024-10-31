// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import Controllers 1.0
import components 1.0
import App

Item {
    id: window
    width: parent.width
    height: parent.height
    visible: true
    property TaskManager eventDatabase: mainController.ui_taskManager

    readonly property date currentDate: new Date()

    // header:ToolBar {
    //     Label {
    //         text: window.currentDate.toLocaleString(locale, "MMMM yyyy")
    //         font.pixelSize: Qt.application.font.pixelSize * 1.25
    //         anchors.centerIn: parent
    //     }
    // }

    GridLayout {
        anchors.fill: parent
        columns: 1

        DayOfWeekRow {
            id: dayOfWeekRow
            locale: grid.locale
            font.bold: false
            delegate: Label {
                text: model.shortName
                font: dayOfWeekRow.font
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter   
            }

            Layout.column: 0
            //Layout.column: 1
            Layout.fillWidth: true
            Rectangle{
                anchors.fill: parent
                color: Style.secondary
            }
        }

        /*WeekNumberColumn {
            month: grid.month
            year: grid.year
            locale: grid.locale
            font.bold: false

            Layout.fillHeight: true
            Rectangle{
                anchors.fill: parent
                color:"green"
            }
        }*/

        MonthGrid {
            id: grid
            month: window.currentDate.getMonth()
            year: window.currentDate.getFullYear()
            spacing: 0

            readonly property int gridLineThickness: 1

            Layout.fillWidth: true
            Layout.fillHeight: true

            delegate: MonthGridDelegate {
                id: gridDelegate
                visibleMonth: grid.month
                eventDatabase: window.eventDatabase
            }

            background: Item {
                x: grid.leftPadding
                y: grid.topPadding
                width: grid.availableWidth
                height: grid.availableHeight

                Rectangle{
                    anchors.fill: parent
                    // color:"grey"
                }

                // Vertical lines
                Row {
                    spacing: (parent.width - (grid.gridLineThickness * rowRepeater.model)) / rowRepeater.model

                    Repeater {
                        id: rowRepeater
                        model: 7
                        delegate: Rectangle {
                            width: 1
                            height: grid.height
                            color: "#ccc"
                        }
                    }
                }

                // Horizontal lines
                Column {
                    spacing: (parent.height - (grid.gridLineThickness * columnRepeater.model)) / columnRepeater.model

                    Repeater {
                        id: columnRepeater
                        model: 6
                        delegate: Rectangle {
                            width: grid.width
                            height: 1
                            color: "#ccc"
                        }
                    }
                }
            }
        }
    }
}
