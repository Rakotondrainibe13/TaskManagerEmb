#include "../include/recurring_task.h"

RecurringTask::RecurringTask(const QString &title, Priority priority) :
    Task(title, priority),
    m_frequency(1),
    m_frequencyUnit("daily")
{
    this->setType("Recurring");
}
