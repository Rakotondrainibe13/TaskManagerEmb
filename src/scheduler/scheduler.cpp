#include "scheduler.h"
#include <algorithm>

Scheduler::Scheduler(QObject *parent) : QObject(parent) {}

void Scheduler::scheduleTasks(const QList<Task*>& tasks) {
    QList<Task*> scheduledTasks = tasks;
    prioritizeTasks(scheduledTasks);
    resolveConflicts(scheduledTasks);
    // Implémenter la logique de planification
}

void Scheduler::prioritizeTasks(QList<Task*>& tasks) {
    // Trier les tâches par priorité et date d'échéance
    std::sort(tasks.begin(), tasks.end(), [](const Task* a, const Task* b) {
        if (a->priority() != b->priority()) {
            return a->priority() > b->priority();
        }
        return a->dueDate() < b->dueDate();
    });
}

void Scheduler::resolveConflicts(QList<Task*>& tasks) {
    // Implémenter la logique de résolution des conflits
}