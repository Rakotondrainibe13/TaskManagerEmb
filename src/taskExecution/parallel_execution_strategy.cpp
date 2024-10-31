#include "parallel_execution_strategy.h"
#include "../include/project_task.h"

namespace TaskExecution{

ParallelExecutionStrategy::~ParallelExecutionStrategy(){

}

void ParallelExecutionStrategy::execute(Task* task){
    ProjectTask* projetTask=dynamic_cast<ProjectTask*>(task);
    QList<TaskPtr> subtasks=projetTask->getSubtasksObj();
    for(TaskPtr subtask:subtasks){
        Task* sub=subtask.get();
        QThreadPool::globalInstance()->start(sub, QThread::NormalPriority);
        subtask=std::shared_ptr<Task>(std::move(sub));
    }
    int status = static_cast<int>(task->getStatus());
    if(status < 2)
        task->setStatus(static_cast<Task::Status>(status+1));
}
}

