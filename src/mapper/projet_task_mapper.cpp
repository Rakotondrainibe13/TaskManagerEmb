#include "../include/projet_task_mapper.h"

void ProjetTaskMapper::map(QSqlQuery& query) {
    results->addSubtask(query.value("subtask_id").toInt());
}
