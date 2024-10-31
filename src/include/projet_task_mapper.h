#ifndef PROJET_TASK_MAPPER_H
#define PROJET_TASK_MAPPER_H
#include "imodel_mapper.h"
#include "project_task.h"


class ProjetTaskMapper : public IModelMapper{
public :
    ProjetTaskMapper(ProjectTask* results) :
        results(results)
        {};
    void map(QSqlQuery& query) override;

private :
    ProjectTask* results;
};


#endif // PROJET_TASK_MAPPER_H
