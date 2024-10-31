#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <include/task.h>

class StatisticsModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(double todoValue READ todoValue NOTIFY todoValueChanged)
    Q_PROPERTY(double inProgressValue READ inProgressValue NOTIFY inProgressValueChanged)
    Q_PROPERTY(double completedValue READ completedValue NOTIFY completedValueChanged)
    Q_PROPERTY(double delayedValue READ delayedValue NOTIFY delayedValueChanged)
    Q_PROPERTY(QList<QString> delayedTasks READ delayedTasks NOTIFY delayedTasksChanged)
    Q_PROPERTY(QList<int> taskActivity READ taskActivity NOTIFY taskActivityChanged)

public:
    explicit StatisticsModel(QObject *parent = nullptr);

    double todoValue() const;
    double inProgressValue() const;
    double completedValue() const;
    double delayedValue() const;
    void updateStatistics();
    Q_INVOKABLE void refreshStatistics();
    void setTodoValue(double value);
    void setInProgressValue(double value);
    void setCompletedValue(double value);
    void setDelayedValue(double value);

    QList<QString> delayedTasks() const;

    Q_INVOKABLE void fetchDelayedTasks();
    QList<int> taskActivity() const;
    QList<int> fetchTaskActivityByDay() const { return m_taskActivity; }

signals:
    void todoValueChanged();
    void inProgressValueChanged();
    void completedValueChanged();
    void delayedValueChanged();
    void delayedTasksChanged();
    void taskActivityChanged();

private:
    double m_todoValue;
    double m_inProgressValue;
    double m_completedValue;
    double m_delayedValue;
    QList<QString> m_delayedTasks;
    QList<int> m_taskActivity;

};
