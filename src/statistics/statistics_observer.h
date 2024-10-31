#pragma once

#include <string>

class StatisticsObserver {
public:
    virtual ~StatisticsObserver() = default;
    virtual void update(const std::string& statistic, double value) = 0;
};