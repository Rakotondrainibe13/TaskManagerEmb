// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractListModel>
#include <QDate>
#include <QtQml>

#include "../include/task_manager.h"

#include "../include/task.h"

class EventModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TaskManager *taskManager READ taskManager WRITE setTaskManager NOTIFY taskManagerChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    QML_ELEMENT
    // Q_MOC_INCLUDE("${TASK_MANAGER_INCLUDE_PATH}/include/task_manager.h")

public:
    EventModel(QObject *parent = nullptr);

    enum ContactRole {
        NameRole = Qt::UserRole,
        EndDateRole
    };
    Q_ENUM(ContactRole)

    TaskManager *taskManager();
    void setTaskManager(TaskManager *taskManager);

    QDate date() const;
    void setDate(QDate date);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

signals:
    void taskManagerChanged();
    void dateChanged();

private:
    bool isValid() const;
    void repopulate();

    TaskManager *m_taskManager = nullptr;
    QDate m_date;
    QList<TaskPtr> m_events;
};

#endif // CONTACTMODEL_H
