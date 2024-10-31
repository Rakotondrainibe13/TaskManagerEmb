#ifndef SIMPLE_EXECUTION_STRATEGY_H
#define SIMPLE_EXECUTION_STRATEGY_H
#include "itask_execution_strategy.h"

namespace TaskExecution{

class SimpleExecutionStrategy: public ITaskExecutionStrategy{
public:
    ~SimpleExecutionStrategy();
    void execute(Task* task) override;
};
}

#endif // SIMPLE_EXECUTION_STRATEGY_H
