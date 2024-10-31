#ifndef TASK_FACTORY_H
#define TASK_FACTORY_H

#include "task.h"
#include <QString>


class TaskFactory : public QObject{
    Q_OBJECT
public:
    enum class TaskType {
        Simple ,
        Recurring ,
        Project
    };

    explicit TaskFactory(QObject *parent = nullptr);
    static TaskPtr createTask(TaskType type, const QString& title, Task::Priority priority = Task::Priority::Medium);
};

#endif // TASK_FACTORY_H
