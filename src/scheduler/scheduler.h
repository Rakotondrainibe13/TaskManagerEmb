// Scheduler.h
#pragma once
#include <QObject>
#include <QList>
#include "Task.h"

class Scheduler : public QObject {
    Q_OBJECT
public:
    explicit Scheduler(QObject *parent = nullptr);
    void scheduleTasks(const QList<Task*>& tasks);

private:
    void prioritizeTasks(QList<Task*>& tasks);
    void resolveConflicts(QList<Task*>& tasks);
    // Autres méthodes privées pour l'algorithme de planification
};