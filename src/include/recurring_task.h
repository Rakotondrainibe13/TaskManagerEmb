#ifndef RECURRING_TASK_H
#define RECURRING_TASK_H
#include "task.h"

class RecurringTask : public Task
{
public:
    RecurringTask(const QString& title, Priority priority = Priority::Medium);
    QString getType() const override { return "Recurring"; }

    int getFrequency() const { return m_frequency; }
    void setFrequency(int frequency) { m_frequency = frequency; }

    QString getFrequencyUnit() const { return m_frequencyUnit; }
    void setFrequencyUnit(const QString& unit) { m_frequencyUnit = unit; }

private:
    int m_frequency;
    QString m_frequencyUnit; // "daily", "weekly", "monthly", etc.
};

#endif // RECURRING_TASK_H
