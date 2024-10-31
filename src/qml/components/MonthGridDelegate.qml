// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import Controllers 1.0
import assets 1.0
import App
ColumnLayout {
    id: root

    property TaskManager eventDatabase

    required property bool today
    required property int year
    required property int month
    required property int day

    required property int visibleMonth

    Material.theme: today ? Material.Dark : undefined

    Label {
        id: dayText
        horizontalAlignment: Text.AlignHCenter
        topPadding: 4
        opacity: month === root.visibleMonth ? 1 : 0
        text: day

        Layout.fillWidth: true

        Rectangle {
            width: height
            height: Math.max(dayText.implicitWidth, dayText.implicitHeight)
            radius: 5
            color: Style.secondary
            anchors.centerIn: dayText
            anchors.verticalCenterOffset: dayText.height - dayText.baselineOffset
            z: -1
            visible: root.today
        }
    }

    ListView {
        spacing: 1
        clip: true

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.topMargin: 4

        delegate: ItemDelegate {
            id: itemDelegate
            width: parent.width
            text: name
            font.pixelSize: Qt.application.font.pixelSize * 0.8
            leftPadding: 4
            rightPadding: 4
            topPadding: 4
            bottomPadding: 4
            required property string name

            Material.theme: Material.Dark

            background: Rectangle {
                color: Style.secondary
                border.width: 1
                radius: Style.borderRadiusField
            }
        }
        model: EventModel {
            taskManager: eventDatabase
            date: new Date(root.year, root.month, root.day)
        }
    }
}
