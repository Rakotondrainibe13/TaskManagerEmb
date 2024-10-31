#ifndef PRODUCTIVITYREPORT_H
#define PRODUCTIVITYREPORT_H
#include "report_template.h"
#include "../include/task.h"
#include <vector>
#include <QObject>

class ProductivityReport :public QObject ,public ReportTemplate{
    Q_OBJECT
    Q_PROPERTY(int totalTasks READ totalTasks NOTIFY totalTasksChanged)
    Q_PROPERTY(int completedTasks READ completedTasks NOTIFY completedTasksChanged)
    Q_PROPERTY(double completionRate READ completionRate NOTIFY completionRateChanged)

public:
    explicit ProductivityReport(const QList<TaskPtr>& tasks, QObject* parent = nullptr);
    double completionRate() const;
    int completedTasks() const;
    int totalTasks() const;

// protected:
    void gatherData() override;
    void analyzeData() override;
    void formatReport() override;

signals:
    void totalTasksChanged();
    void completedTasksChanged();
    void completionRateChanged();

private:
    const QList<TaskPtr>& m_tasks;
    double m_completionRate;
    int m_completedTasks;
    int m_totalTasks;
};
#endif // PRODUCTIVITYREPORT_H
