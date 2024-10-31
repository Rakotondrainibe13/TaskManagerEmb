#pragma once
#include <QString>
#include <QObject>
#include "database_manager.h"
#include "task_observer.h"
#include "notification/notification.h"

class NotificationManager : public QObject, public TaskObserver
{
    Q_OBJECT
public:
    static NotificationManager& getInstance(const std::shared_ptr<DatabaseManager> &dbManager, QObject *parent = nullptr);

    void createNotification(const QString &message, const QString &level);


    // Create notification
    void createNotification(const QString &message, int userId, int taskId, Notification::NotificationType typeEvent, const QString &level);


    QList<Notification*> getUnreadNotifications();

    // Implementation of virtual function
    void onTaskEvent(const TaskPtr &task, TaskObserver::TaskEvent event) override;
    void onTaskAssigned(const TaskPtr &task, int userAssignedId) override;

    void notifyUsers(QList<User*> &users, const TaskPtr &task, Notification::NotificationType typeEvent, const QString &level);

    // Get the number on unread notifications
    int countUnreadNotification();

    // Read a notification
    void readNotification(int notificationId);
signals:
    // void notificationCreated(const QString &message , const QString &level);
    // void creatingNotification(const QString &message , const QString &level);
    void creatingNotification();
    void readNotificationSignal();


private:
    explicit NotificationManager(QObject* parent = nullptr);
    NotificationManager(const std::shared_ptr<DatabaseManager> &dbManager, QObject *parent = nullptr);

    // avoid copy and assignment hre
    NotificationManager(const NotificationManager&) = delete;
    void operator =(const NotificationManager&) = delete;

    std::shared_ptr<DatabaseManager> m_dbManager;
    QList<Notification*> m_activeNotifications;
};
