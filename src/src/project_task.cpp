#include "../include/project_task.h"

QList<int> ProjectTask::subtasks() const
{
    return m_subtasks;
}

ProjectTask::ProjectTask(const QString &title, Priority priority) :
    Task(title, priority)
{
    this->setType("Project");
}

void ProjectTask::addSubtask(TaskPtr subtask) {
    if (std::find(m_subtasks.begin(), m_subtasks.end(), subtask->getId()) == m_subtasks.end()) {
        m_subtasks.append(subtask->getId());
    }
}

void ProjectTask::addSubtask(int subtaskId) {
    if (std::find(m_subtasks.begin(), m_subtasks.end(), subtaskId) == m_subtasks.end()) {
        m_subtasks.append(subtaskId);
    }
}

void ProjectTask::removeSubtask(TaskPtr subtask) {
    m_subtasks.removeOne(subtask->getId());
}

QList<TaskPtr> ProjectTask::getSubtasksObj() const
{
    return m_subtasksObj;
}

void ProjectTask::setSubtasksObj(const QList<TaskPtr>& subtasksObj){
    m_subtasksObj=subtasksObj;
}

