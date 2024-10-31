#pragma once

#include <vector>
#include <string>
#include "statistics_observer.h"

class StatisticsSubject {
private:
    std::vector<StatisticsObserver*> observers;
public:
    void attach(StatisticsObserver* observer);
    void notify(const std::string& statistic, double value);
};
