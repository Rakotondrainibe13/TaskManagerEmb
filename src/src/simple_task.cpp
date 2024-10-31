#include "../include/simple_task.h"

SimpleTask::SimpleTask(const QString& title, Priority priority)
    : Task(title, priority)
{
    this->setType("Simple");
}
