#ifndef PARALLEL_EXECUTION_STRATEGY_H
#define PARALLEL_EXECUTION_STRATEGY_H
#include "itask_execution_strategy.h"

namespace TaskExecution{

class ParallelExecutionStrategy: public ITaskExecutionStrategy{
public:
    ~ParallelExecutionStrategy();
    void execute(Task* task) override;

};
}

#endif // PARALLEL_EXECUTION_STRATEGY_H
