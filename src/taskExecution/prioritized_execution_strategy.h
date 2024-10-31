#ifndef PRIORITIZED_EXECUTION_STRATEGY_H
#define PRIORITIZED_EXECUTION_STRATEGY_H
#include "itask_execution_strategy.h"

namespace TaskExecution{

class PrioritizedExecutionStrategy: public ITaskExecutionStrategy{
public:
    ~PrioritizedExecutionStrategy();
    void execute(Task* task) override;
};
}

#endif // PRIORITIZED_EXECUTION_STRATEGY_H
