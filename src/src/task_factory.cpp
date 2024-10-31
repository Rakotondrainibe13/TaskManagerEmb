#include "../include/task_factory.h"
#include"../include/simple_task.h"
#include"../include/project_task.h"
#include"../include/recurring_task.h"
#include <stdexcept>

TaskFactory::TaskFactory(QObject *parent): QObject(parent){}

TaskPtr TaskFactory::createTask(TaskType type, const QString &title, Task::Priority priority)
{
    switch(type) {
        case TaskType::Simple:
            return std::make_shared<SimpleTask>(title, priority);
        case TaskType::Recurring:
            return std::make_shared<RecurringTask>(title, priority);
        case TaskType::Project:
            return std::make_shared<ProjectTask>(title, priority);
        default:
            throw std::invalid_argument("Unkown TaskType provided");
    }
}
