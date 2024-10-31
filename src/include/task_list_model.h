#ifndef TASK_LIST_MODEL_H
#define TASK_LIST_MODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "task_manager.h"
#include "task.h"
#include <vector>

class TaskListModel : public QAbstractListModel
{
public:
    enum TaskRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        DueDateRole,
        DescriptionRole
    };
    explicit TaskListModel(TaskManager * taskManager, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void updateTasks();

private:
    TaskManager* m_taskManager;
    QList<Task*> m_tasks;
};

#endif // TASK_LIST_MODEL_H
