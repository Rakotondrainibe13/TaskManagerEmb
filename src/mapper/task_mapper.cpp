#include "../include/task_mapper.h"
#include <QSqlError>
#include <QDebug>

void TaskMapper::map(QSqlQuery& query) {
    TaskPtr task = m_taskFactory->createTask( TaskMapper::toTaskType(query.value("type").toString()), query.value("title").toString());
    // TaskPtr task=std::make_shared<Task>(query.value("title").toString(), static_cast<Task::Priority>(query.value("priority").toInt()));
    task->setId(query.value("id").toInt());
    task->setDescription(query.value("description").toString());
    task->setPriority(static_cast<Task::Priority>(query.value("priority").toInt()));
    task->setStatus(static_cast<Task::Status>(query.value("status").toInt()));
    task->setDueDate(query.value("due_Date").toDateTime());
    results.append(task);
};

TaskFactory::TaskType TaskMapper::toTaskType(const QString& string) {
    if(string == "Simple"){
        return TaskFactory::TaskType::Simple;
    }if(string =="Recurring"){
        return TaskFactory::TaskType::Recurring;
    }if(string == "Project"){
        return TaskFactory::TaskType::Project;
    }
    throw std::invalid_argument("Unkown TaskType provided");
}
