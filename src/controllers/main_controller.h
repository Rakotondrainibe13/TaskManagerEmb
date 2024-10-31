#pragma once
#include <QObject>
#include <QQmlListProperty>
#include "../include/task_manager.h"
#include "../include/database_manager.h"
#include "../include/security_manager.h"
#include "../include/network_manager.h"
#include "../include/task_factory.h"
#include "../include/task.h"
#include "navigation_controller.h"
#include "../include/form_validator.h"
#include "../include/notification_manager.h"
#include "../include/authorization_manager.h"
#include "../include/user_manager.h"
#include "../include/synch_manager.h"
#include "../iterator/task_iterator.h"

#include "../include/subscription_manager.h"
#include <QSharedPointer>
#include "report/productivityReport.h"
#include "statistics/statistics_model.h"
#include "../include/task_list_model.h"
#include <QtConcurrent>

namespace controllers {
class MainController : public QObject {
    Q_OBJECT
    // Q_PROPERTY(QList<Task*> tasks MEMBER m_tasks NOTIFY tasksChanged)
    Q_PROPERTY(QList<Task*> tasks READ getAllTasks NOTIFY tasksChanged)
    Q_PROPERTY(SecurityManager* securityEvent READ securityManager)
    Q_PROPERTY(TaskManager* ui_taskManager READ taskManager)
    Q_PROPERTY(SynchManager* synchManager READ synchManager)
    Q_PROPERTY(NavigationController* ui_navigationController READ navigationController CONSTANT)
    Q_PROPERTY(FormValidator* formValidator READ formValidator CONSTANT)
    Q_PROPERTY(bool hasPrevious READ hasPrevious NOTIFY tasksChanged)
    Q_PROPERTY(bool hasNext READ hasNext NOTIFY tasksChanged)
    Q_PROPERTY(SubscriptionManager* ui_subscriptionManager READ subscriptionManager NOTIFY ui_subscriptionManagerChanged)
    Q_PROPERTY(int countNotification READ countNotification NOTIFY countNotificationChanged FINAL)
    Q_PROPERTY(QList<Notification*> unreadNotification READ unreadNotification NOTIFY unreadNotificationChanged FINAL)

    Q_PROPERTY(SubscriptionManager* ui_subscriptionManager READ subscriptionManager)

    Q_PROPERTY(ProductivityReport* report READ report NOTIFY reportChanged)

    Q_PROPERTY(StatisticsModel* statisticmodel READ statisticmodel NOTIFY statisticChanged)

    Q_PROPERTY(TaskListModel * taskListModel READ taskListModel)


public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();
    void testSecurityFunctions();
    // Q_INVOKABLE void createNotification(const QString &message, const QString &level);
    Q_INVOKABLE void createTask(const QString& title, const QString& description, int priority, const QString& dueDate, int type);
    Q_INVOKABLE bool updateTask(int taskId, const QString& title, const QString& description, int priority, const QString& dueDate);
    Q_INVOKABLE void deleteTask(int taskId);
    Q_INVOKABLE void executeTask(int taskId);
    Q_INVOKABLE void login(const QString& username, const QString& password);
    Q_INVOKABLE void logout();
    Q_INVOKABLE bool hasAccess(const QString &resource) const;
    Q_INVOKABLE Task* getTaskPtrById(const int& id);
    // Q_INVOKABLE void syncTasks();
    Q_INVOKABLE QList<QObject*> getUsersAsQObjects();
    Q_INVOKABLE void updateUserRole(const QString& userID, const QString& role);
    Q_INVOKABLE void nextPage();
    Q_INVOKABLE void previousPage();
    Q_INVOKABLE void applyFilter(const QString& searchText);
    Q_INVOKABLE void applySort(int sortType);
    Q_INVOKABLE QList<UserPtr> getUsersAssignedTask(const int& taskId);
    Q_INVOKABLE QList<UserPtr> getUsersNotAssignedTask(const int& taskId);
    Q_INVOKABLE bool unassignmentTaskUser(const int& taskId, const int& userId);
    Q_INVOKABLE bool assignmentTaskUser(const int& taskId, const QList<int> idUsers);
    Q_INVOKABLE void doSync();
    Q_INVOKABLE void updateRetentionConfig(const QString& mois, const QString& jour, const QString& heure, const QString& minute);
    Q_INVOKABLE void generateReport();
    Q_INVOKABLE void readNotification(int notificationId);

    Q_INVOKABLE void createTaskAsync(const QString& title, const QString& description, int priority, const QString& dueDate, int type);
    Q_INVOKABLE void updateTaskAsync(int taskId, const QString &title, const QString &description, int priority, const QString &dueDate);
    Q_INVOKABLE bool assignmentTaskUserAsync(const int &taskId, const QList<int> idUsers);
    Q_INVOKABLE void deleteTaskAsync(int taskId);
    // Q_INVOKABLE void fetchTaskDetailsAsync(int taskId);


    NavigationController* navigationController();
    FormValidator* formValidator();
    SecurityManager* securityManager();
    TaskManager* taskManager();
    SynchManager* synchManager();
    void initTasks();
    TaskPtr getTaskById(const int id) const;
    QList<UserPtr> getAllUsers() const;
    ProductivityReport* report() const;

    bool hasPrevious() const;
    bool hasNext() const;

    int countNotification();
    int countTaskNumber();
    SubscriptionManager *subscriptionManager() const;
    QList<Task*> getAllTasks();

    StatisticsModel* statisticmodel() const;

    QList<Notification *> unreadNotification();

    void firstInitDb();
    TaskListModel * taskListModel() const;


signals:
    void tasksChanged();
    void loginStatusChanged();
    void errorOccurred(const QString& errorMessage);
    void notificationCreated(const QString &message, const QString &level);
    void userRoleUpdated(int userID, const QString& role);
    void loginStatusError(const QString & errorMessage);
    void ui_subscriptionManagerChanged();
    void ui_taskCreated();
    void reportChanged();
    void statisticChanged();

    void updateUsersAssignment();

    void countNotificationChanged();

    void unreadNotificationChanged();
    void taskUpdated(bool ret);

private slots:
    void onTaskCreated(TaskPtr task);
    void onTaskUpdated(TaskPtr task);
    void onTaskDeleted(int taskId);
    void onSecurityEvent(const QString& event);
    void onNetworkStatusChanged(bool isConnected);
    // void handleInternalNotification(const QString &message, const QString &level);

    // void handleInternalNotification(const QString &message, const QString &level);
    
private:
    std::unique_ptr<NavigationController> m_navigationController;
    std::unique_ptr<FormValidator> m_formValidator;
    void connectManagers();
    // void loadTasks();

    std::unique_ptr<TaskManager> m_taskManager;
    std::shared_ptr<DatabaseManager> m_dbManager;
    std::unique_ptr<SecurityManager> m_securityManager;
    NetworkManager &m_networkManager = NetworkManager::instance();

    std::shared_ptr<TaskFactory> m_taskFactory;

    std::unique_ptr<AuthorizationManager> m_authorizationManager;
    std::unique_ptr<UserManager> m_userManager;
    std::shared_ptr<SynchManager> m_synchManager;
    std::unique_ptr<TaskIterator> m_taskIterator;
    std::shared_ptr<SubscriptionManager> m_subscriptionManager;

    QList<Task*> m_tasks;
    void emitTasksChanged(const QList<TaskPtr>& tasks);
    std::unique_ptr<ProductivityReport> m_report;
    std::unique_ptr<StatisticsModel> m_statistic;

    QThreadPool m_threadPool;
    TaskListModel * m_taskListModel;

};
}
