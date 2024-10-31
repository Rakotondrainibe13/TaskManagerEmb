#ifndef SIMPLE_TASK_H
#define SIMPLE_TASK_H
#include "task.h"
#include <QString>

class SimpleTask : public Task
{
public:
    SimpleTask(const QString& title, Priority priority = Priority::Medium);
    QString getType() const override
    {
        return "Simple";
    }
};

#endif // SIMPLE_TASK_H
