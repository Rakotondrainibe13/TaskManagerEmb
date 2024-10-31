#pragma once

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>
#include <QDate>

#include "task.h"
#include "project_task.h"
#include "task_observer.h"
#include "task_factory.h"
#include "../iterator/task_iterator.h"
#include "../taskExecution/itask_execution_strategy.h"
#include "../taskExecution/simple_execution_strategy.h"
#include "../taskExecution/parallel_execution_strategy.h"
#include "../taskExecution/sequential_execution_strategy.h"
#include "database_manager.h"
#include "user.h"
#include "report/productivityReport.h"
#include "statistics/statistics_model.h"
#include "subscription_manager.h"
#include "max_task_exception.h"
#include <QSharedPointer>

class TaskManager : public QObject {
    Q_OBJECT
public:
    explicit TaskManager(QObject *parent = nullptr);
    explicit TaskManager(std::shared_ptr<TaskFactory> taskFactory,std::shared_ptr<DatabaseManager> databaseManager, QObject *parent = nullptr);

    // Méthodes de gestion des tâches
    bool updateTask(TaskPtr task);
    void updateStatus(TaskPtr& task);
    void removeTask(int taskId);
    TaskPtr getTask(int taskId) const;
    QList<TaskPtr> getAllTasks() const;
    QList<TaskPtr> getAllTasksByIdUser(int userId) const;
    QList<TaskPtr> getAllTasksAtAGivenDate(const QDate& date) const;
    std::unique_ptr<TaskIterator> createIterator(int& pageSize) const;
    void populateSubtask(ProjectTask* projetTask);
    QList<User*> usersAssigned(int taskId);
    QList<User*> usersNotAssigned(int taskId);
    bool unassignmentUser(int taskId, int userId);
    bool assignmentUser(int taskId, const QList<int>& idUsers);
    int countTasks();

    // Méthodes liées au pattern Composite
    void addSubtask(int parentTaskId, TaskPtr subtask);
    void removeSubtask(int parentTaskId, int subtaskId);

    // Méthodes liées au pattern Observer
    void registerObserver(TaskObserver* observer);
    void unregisterObserver(TaskObserver* observer);

    // Méthodes liées au pattern Strategy
    void setExecutionStrategy(std::shared_ptr<TaskExecution::ITaskExecutionStrategy> strategy);
    void executeTask(Task* task);
    void taskExecutionStrategy(Task* task);
    void executionTask(int taskId);

    // Méthodes liées au pattern Factory
    TaskPtr createTask(const QString& title, const QString& description, int priority, const QDateTime& dueDate, int type);

    // Méthodes pour l'itération
    std::unique_ptr<TaskIterator> createIterator();

    //Methodes pour les rapports
    std::unique_ptr<ProductivityReport> generateReport(int user_id);
    std::unique_ptr<StatisticsModel> calculateStatistics();
    QList<TaskPtr> getAllOverdueTasks() const;

    std::shared_ptr<SubscriptionManager> subscriptionManager() const;
    void setSubscriptionManager(const std::shared_ptr<SubscriptionManager> &newSubscriptionManager);

signals:
    void taskAdded(TaskPtr task);
    void taskRemoved(int taskId);
    void taskUpdated(TaskPtr task);
    void maxTaskNumberReached(QString errorMessage);
    void updatedTaskSignal(const int& id);
    void userAssignmentChanged();

private slots:
    void onOverdueTasks();

private:
    QMap<int, TaskPtr> m_tasks;
    QList<TaskObserver*> m_observers;
    std::shared_ptr<TaskExecution::ITaskExecutionStrategy> m_executionStrategy;
    std::shared_ptr<TaskFactory> m_taskFactory;
    std::shared_ptr<DatabaseManager> m_dbManager;
    std::shared_ptr<SubscriptionManager> m_subscriptionManager;
    static constexpr int MAX_FREE_TASK_NUMBER = 3;
};

