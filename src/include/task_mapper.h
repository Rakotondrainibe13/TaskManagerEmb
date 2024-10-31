#ifndef TASK_MAPPER_H
#define TASK_MAPPER_H

#include "imodel_mapper.h"
#include "task.h"
#include "task_factory.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <vector>

class TaskMapper : public IModelMapper{
    public :
        TaskMapper(QList<TaskPtr>& results, std::shared_ptr<TaskFactory> taskFactory) :
            results(results),
            m_taskFactory(taskFactory)
        {};
        void map(QSqlQuery& query) override;

    private :
        static TaskFactory::TaskType toTaskType(const QString& string);

        QList<TaskPtr>& results;
        std::shared_ptr<TaskFactory> m_taskFactory;
};   

#endif
