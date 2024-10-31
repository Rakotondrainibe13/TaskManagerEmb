#ifndef TASK_MAPPER_H
#define TASK_MAPPER_H

#include "imodel_mapper.h"
#include "../include/user.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class UserMapper : public IModelMapper{
public :
    UserMapper(QList<UserPtr>& results) :
        results(results)
        {};
    void map(QSqlQuery& query) override;

private :
    QList<UserPtr>& results;
};

#endif
