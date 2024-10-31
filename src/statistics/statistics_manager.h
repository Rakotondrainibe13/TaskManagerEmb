#pragma once

#include <vector>
#include "../include/task.h"
#include "statistics_subject.h"
#include <memory>
#include "statistics_observer.h"

class StatisticsManager : public StatisticsSubject {
public:
    void calculateStatistics(const std::vector<std::shared_ptr<Task>>& tasks);

private:
    double calculateCompletionRate(const std::vector<std::shared_ptr<Task>>& tasks);
    double calculatePendingRate(const std::vector<std::shared_ptr<Task>>& tasks);
    double calculateInProgressRate(const std::vector<std::shared_ptr<Task>>& tasks);
    double calculateDelayedRate(const std::vector<std::shared_ptr<Task>>& tasks);
};
