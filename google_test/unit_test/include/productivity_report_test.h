#pragma once
#include "../../../src/include/task_factory.h"
#include "../../../src/include/task.h"
#include "../../../src/report/productivityReport.h"

TaskPtr createTask(const QString& name, Task::Status status) {
    TaskPtr task = std::make_shared<Task>();
    task->setStatus(status);
    task->setTitle(name);
    return task;
}

TEST(ProductivityReportTest, AnalyzeDataWithNoTasks) {
    QList<TaskPtr> tasks;
    ProductivityReport report(tasks,nullptr);

    report.analyzeData();

    EXPECT_EQ(report.totalTasks(), 0);
    EXPECT_EQ(report.completedTasks(), 0);
    EXPECT_DOUBLE_EQ(report.completionRate(), 0.0);
}

TEST(ProductivityReportTest, AnalyzeDataWithSomeCompletedTasks) {
    QList<TaskPtr> tasks;
    tasks.append(createTask("Task 1", Task::Status::Completed));
    tasks.append(createTask("Task 2", Task::Status::InProgress));
    tasks.append(createTask("Task 3", Task::Status::Completed));

    ProductivityReport report(tasks,nullptr);

    report.analyzeData();

    EXPECT_EQ(report.totalTasks(), 3);
    EXPECT_EQ(report.completedTasks(), 2);
    EXPECT_DOUBLE_EQ(report.completionRate(), (2.0 / 3.0) * 100.0);
}

TEST(ProductivityReportTest, AnalyzeDataWithAllTasksCompleted) {
    QList<TaskPtr> tasks;
    tasks.append(createTask("Task 1", Task::Status::Completed));
    tasks.append(createTask("Task 2", Task::Status::Completed));
    tasks.append(createTask("Task 3", Task::Status::Completed));

    ProductivityReport report(tasks);

    report.analyzeData();

    EXPECT_EQ(report.totalTasks(), 3);
    EXPECT_EQ(report.completedTasks(), 3);
    EXPECT_DOUBLE_EQ(report.completionRate(), 100.0);
}

