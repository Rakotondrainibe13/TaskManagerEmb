#include "statistics_manager.h"
#include <iostream>

void StatisticsManager::calculateStatistics(const std::vector<std::shared_ptr<Task>>& tasks) {
    // Calculate different statistics
    double completionRate = calculateCompletionRate(tasks);
    double pendingRate = calculatePendingRate(tasks);
    double inProgressRate = calculateInProgressRate(tasks);
    double delayedRate = calculateDelayedRate(tasks);

    // Notify observers with the updated statistics
    notify("CompletionRate", completionRate);
    notify("PendingRate", pendingRate);
    notify("InProgressRate", inProgressRate);
    notify("DelayedRate",delayedRate);
}

double StatisticsManager::calculateCompletionRate(const std::vector<std::shared_ptr<Task>>& tasks) {
    int completedTasks = 0;
    for (const auto& task : tasks) {
        if (task->getStatus() == Task::Status::Completed) {
            completedTasks++;
        }
    }
    return tasks.empty() ? 0.0 : (static_cast<double>(completedTasks) / tasks.size()) * 100.0;
}

double StatisticsManager::calculatePendingRate(const std::vector<std::shared_ptr<Task>>& tasks) {
    int pendingTasks = 0;
    for (const auto& task : tasks) {
        if (task->getStatus() == Task::Status::NotStarted) {
            pendingTasks++;
        }
    }
    return tasks.empty() ? 0.0 : (static_cast<double>(pendingTasks) / tasks.size()) * 100.0;
}

double StatisticsManager::calculateInProgressRate(const std::vector<std::shared_ptr<Task>>& tasks) {
    int inProgressTasks = 0;
    for (const auto& task : tasks) {
        if (task->getStatus() == Task::Status::InProgress) {
            inProgressTasks++;
        }
    }
    return tasks.empty() ? 0.0 : (static_cast<double>(inProgressTasks) / tasks.size()) * 100.0;
}

double StatisticsManager::calculateDelayedRate(const std::vector<std::shared_ptr<Task>>& tasks) {
    int delayedTasks = 0;
    for (const auto& task : tasks) {
        if (task->getDueDate() < QDateTime::currentDateTime()) {  // Assuming Task has an isDelayed() method
            delayedTasks++;
        }
    }
    return tasks.empty() ? 0.0 : (static_cast<double>(delayedTasks) / tasks.size()) * 100.0;
}
