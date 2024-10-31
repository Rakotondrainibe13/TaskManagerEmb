#ifndef TASK_OBSERVER_H
#define TASK_OBSERVER_H
#include "task.h"
#include "user.h"
/**
 * @brief The TaskObserver class
 * Observers that are interested in state changes of the subject: "TaskManager", here
 */
class TaskObserver{
public :

    // Enum to define different task events
    enum class TaskEvent {
        Created,
        Updated,
        Deleted,
        Overdue,
        StatusChanged
    };

    virtual void onTaskEvent(const TaskPtr &task, TaskEvent event);
    virtual void onTaskAssigned(const TaskPtr &task, int userAssignedId);
};

#endif // TASK_OBSERVER_H
