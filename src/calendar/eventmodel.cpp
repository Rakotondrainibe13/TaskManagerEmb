// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "eventmodel.h"

EventModel::EventModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

TaskManager *EventModel::taskManager()
{
    return m_taskManager;
}

void EventModel::setTaskManager(TaskManager *taskManager)
{
    if (taskManager == m_taskManager)
        return;

    m_taskManager = taskManager;
    repopulate();
    emit taskManagerChanged();
}

QDate EventModel::date() const
{
    return m_date;
}

void EventModel::setDate(QDate date)
{
    if (date == m_date)
        return;

    m_date = date;
    repopulate();
    emit dateChanged();
}

int EventModel::rowCount(const QModelIndex &) const
{
    return m_events.size();
}

QVariant EventModel::data(const QModelIndex &index, int role) const
{
    if (!checkIndex(index, CheckIndexOption::IndexIsValid))
        return QVariant();

    switch (role) {
    case NameRole: return m_events.at(index.row())->getTitle();
    case EndDateRole: return m_events.at(index.row())->getDueDate();
    default: return QVariant();
    }
}

QHash<int, QByteArray> EventModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { NameRole, "name" },
        { EndDateRole, "endDate" }
    };
    return roles;
}

bool EventModel::isValid() const
{
    return m_taskManager && !m_date.isNull();
}

void EventModel::repopulate()
{
    beginResetModel();

    if (!m_taskManager || m_date.isNull()) {
        m_events.clear();
        return;
    }

    m_events = m_taskManager->getAllTasksAtAGivenDate(m_date);
    endResetModel();
}
