#include "statistics_subject.h"

void StatisticsSubject::attach(StatisticsObserver* observer) {
    observers.push_back(observer);
}

void StatisticsSubject::notify(const std::string& statistic, double value) {
    for (auto observer : observers) {
        observer->update(statistic, value);
    }
}
