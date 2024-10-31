#ifndef TASK_ITERATOR_H
#define TASK_ITERATOR_H

#include "../include/task.h"
#include <QList>
#include <functional>

class TaskIterator {
public:
    TaskIterator(const QList<TaskPtr>& tasks, int pageSize);

    bool hasNext() const;
    QList<TaskPtr> next();
    bool hasPrevious() const;
    QList<TaskPtr> previous();
    void reset();
    void setFilter(std::function<bool(const TaskPtr&)> filter);
    void setSort(std::function<bool(const TaskPtr&, const TaskPtr&)> sorter);
    void apply();
    QList<TaskPtr> getAllTasks();

private:
    QList<TaskPtr> tasks_;
    QList<TaskPtr> filteredTasks_;
    int pageSize_;
    int currentIndex_;
    std::function<bool(const TaskPtr&)> filter_;
    std::function<bool(const TaskPtr&, const TaskPtr&)> sorter_;
};

#endif // TASK_ITERATOR_H
