#include "task_iterator.h"
#include <algorithm>
#include <QDebug>

TaskIterator::TaskIterator(const QList<TaskPtr>& tasks, int pageSize)
    : tasks_(tasks), pageSize_(pageSize), currentIndex_(0) {
    filteredTasks_ = tasks_;
}

bool TaskIterator::hasNext() const {
    return currentIndex_ < filteredTasks_.size();
}

QList<TaskPtr> TaskIterator::next() {
    if(!hasNext()){
        return{};
    }
    qsizetype endIndex = std::min(static_cast<qsizetype>(currentIndex_ + pageSize_), filteredTasks_.size());
    QList<TaskPtr> page = filteredTasks_.mid(currentIndex_, endIndex - currentIndex_);
    currentIndex_ = endIndex;
    qDebug() << "NEXT CURRENT : " << currentIndex_;
    return page;
}

bool TaskIterator::hasPrevious() const {
    return currentIndex_ > pageSize_;
}

/*QList<TaskPtr> TaskIterator::previous() {
    qsizetype startIndex = std::max(static_cast<qsizetype>(0), static_cast<qsizetype>(currentIndex_ - pageSize_));
    qsizetype endIndex = currentIndex_;

    qDebug() << "previous() called:";
    qDebug() << " - Before update: currentIndex_ =" << currentIndex_;
    qDebug() << " - Calculated startIndex =" << startIndex << ", endIndex =" << endIndex;

    currentIndex_ = startIndex;

    qDebug() << " - After update: currentIndex_ =" << currentIndex_;

    QList<TaskPtr> page = filteredTasks_.mid(startIndex, endIndex - startIndex);
    return page;
}*/

QList<TaskPtr> TaskIterator::previous(){
    qsizetype stepsBack = pageSize_;
    if(currentIndex_ % pageSize_ !=0){
        stepsBack = currentIndex_ % pageSize_;
    }
    qsizetype startIndex = std::max(static_cast<qsizetype>(0), static_cast<qsizetype>(currentIndex_ - stepsBack));
    qsizetype endIndex = currentIndex_;
    currentIndex_ = startIndex;
    QList<TaskPtr> page = filteredTasks_.mid(startIndex, endIndex - startIndex);
    qDebug() << "PREV CURRENT : " << currentIndex_;
    return page;
}

void TaskIterator::reset() {
    currentIndex_ = 0;
}

void TaskIterator::setFilter(std::function<bool(const TaskPtr&)> filter) {
    filter_ = filter;
}

void TaskIterator::setSort(std::function<bool(const TaskPtr&, const TaskPtr&)> sorter) {
    sorter_ = sorter;
}

void TaskIterator::apply() {
    if (filter_) {
        filteredTasks_.clear();
        for (const auto& task : tasks_) {
            if (filter_(task)) {
                filteredTasks_.append(task);
            }
        }
    } else {
        filteredTasks_ = tasks_;
    }

    if (sorter_) {
        std::sort(filteredTasks_.begin(), filteredTasks_.end(), sorter_);
    }

    reset();
}

QList<TaskPtr> TaskIterator::getAllTasks(){
    return filteredTasks_.mid(0,pageSize_);
}
