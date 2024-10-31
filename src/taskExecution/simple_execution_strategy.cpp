#include "simple_execution_strategy.h"

namespace TaskExecution{

SimpleExecutionStrategy::~SimpleExecutionStrategy(){

}

void SimpleExecutionStrategy::execute(Task* task) {
    int status = static_cast<int>(task->getStatus());
    if(status < 2) task->setStatus(static_cast<Task::Status>(status+1));
}
}
