#ifndef PROJECT_TASK_H
#define PROJECT_TASK_H
#include "task.h"
#include <QList>
#include <QString>

class ProjectTask : public Task
{
public:
    ProjectTask(const QString& title, Priority priority = Priority::Medium);
    QString getType() const override { return "Project"; }

    void addSubtask(TaskPtr subtask);
    void addSubtask(int subtaskId);
    void removeSubtask(TaskPtr subtask);

    QList<TaskPtr> getSubtasksObj() const;
    void setSubtasksObj(const QList<TaskPtr>& subtasksObj);


    QList<int> subtasks() const;

private:
    QList<int> m_subtasks;
    QList<TaskPtr> m_subtasksObj;
};

#endif // PROJECT_TASK_H
