#include "sequential_execution_strategy.h"
#include "../include/project_task.h"

namespace TaskExecution{

SequentialExecutionStrategy::~SequentialExecutionStrategy(){

}

void SequentialExecutionStrategy::execute(Task* task) {
    ProjectTask* projetTask=dynamic_cast<ProjectTask*>(task);
    QList<TaskPtr> subtasks=projetTask->getSubtasksObj();

    for(TaskPtr subtask:subtasks){
        int statusSubTask = static_cast<int>(subtask->getStatus());
        QList<TaskPtr> listeDependance = subtask->getDependenciesTasks();
        if(listeDependance.size()>0){
            int allFinished = 0;
            for(int i=0; i<listeDependance.size(); i++){
                int status = static_cast<int>(listeDependance[i]->getStatus());
                if(status < 2){
                    listeDependance[i]->setStatus(static_cast<Task::Status>(status+1));
                    break;
                } else{
                    allFinished++;
                }
            }
            if(allFinished==listeDependance.size()){
                if(statusSubTask < 2) {
                    subtask->setStatus(static_cast<Task::Status>(statusSubTask+1));
                    break;
                }
            }
        }else{
            if(statusSubTask < 2) {
                subtask->setStatus(static_cast<Task::Status>(statusSubTask+1));
                break;
            }
        }
    }
}
}

