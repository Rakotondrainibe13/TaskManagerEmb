#include "../include/task_list_model.h"

TaskListModel::TaskListModel(TaskManager* taskManager, QObject* parent)
    : QAbstractListModel(parent), m_taskManager(taskManager) {
    updateTasks();
}


int TaskListModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid())
        return 0;
    return m_tasks.size();
}

QVariant TaskListModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid() || index.row() >= m_tasks.size())
        return QVariant();

    const auto& task = m_tasks[index.row()];
    switch (role) {
    case IdRole: return task->getId();
    case TitleRole: return task->getTitle();
    case DueDateRole: return task->getDueDate();
    case DescriptionRole: return task->getDescription();
    default: return QVariant();
    }
}

QHash<int, QByteArray> TaskListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "title";
    roles[DueDateRole] = "dueDate";
    roles[DescriptionRole] = "description";
    return roles;
}

void TaskListModel::updateTasks() {
    beginResetModel();
    // QList<TaskPtr> tasksptr = m_taskManager->getAllTasks();
    // for(TaskPtr &ts : tasksptr){
    //     m_tasks.append(ts.get());
    // }
    endResetModel();
}
