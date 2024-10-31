#ifndef IMODEL_MAPPER_H
#define IMODEL_MAPPER_H

#include <QSqlQuery>
#include <QSqlError>

class IModelMapper{
    public : 
        virtual ~IModelMapper() = default;
        virtual void map(QSqlQuery& querry) = 0;    
}; 

#endif