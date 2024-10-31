#ifndef SEQUENTIAL_EXECUTION_STRATEGY_H
#define SEQUENTIAL_EXECUTION_STRATEGY_H
#include "itask_execution_strategy.h"

namespace TaskExecution{

class SequentialExecutionStrategy: public ITaskExecutionStrategy{
public:
    ~SequentialExecutionStrategy();
    void execute(Task* task) override;
};
}

#endif // SEQUENTIAL_EXECUTION_STRATEGY_H
