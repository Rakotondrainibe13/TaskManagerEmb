#ifndef ITASK_EXECUTION_STRATEGY_H
#define ITASK_EXECUTION_STRATEGY_H
#include "../include/task.h"

namespace TaskExecution{
class ITaskExecutionStrategy {
public:
    virtual ~ITaskExecutionStrategy() = default;
    virtual void execute(Task* task) = 0;

};
}

#endif // ITASK_EXECUTION_STRATEGY_H
