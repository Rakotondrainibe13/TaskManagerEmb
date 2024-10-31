#include "../include/notification_manager.h"
#include <QSettings>


/**
 * @brief Get instance from Singleton Notification
 * @param parent
 * @return
 */
NotificationManager& NotificationManager::getInstance(const std::shared_ptr<DatabaseManager> &dbManager, QObject *parent)
{
    static NotificationManager instance_(dbManager, parent);
    return instance_;
}

void NotificationManager::createNotification(const QString &message, const QString &level){
    //insert into base
    // emit creatingNotification(message, level);
}

/**
 * @brief creating notification and save it in dataabse
 * @param message
 * @param userId
 * @param taskId
 * @param notificationTYpe
 */
void NotificationManager::createNotification(const QString &message, int userId, int taskId, Notification::NotificationType typeEvent, const QString &level)
{
    try {
        Notification notification(userId, taskId, message, false, typeEvent, this);
        if(m_dbManager->saveNotification(&notification)){
            emit creatingNotification();
            // emit creatingNotification(message, level);
        }
    } catch (const std::exception& e) {
        qDebug() << (QString("Error adding notification: %1").arg(e.what()));
    }
}

/**
 * @brief NotificationManager::onTaskEvent
 * Depending of the event, we will assign the appropriate notification
 * @param task
 * @param event
 */
void NotificationManager::onTaskEvent(const TaskPtr &task, TaskEvent event)
{
    // On task created
    if(event == TaskEvent::Created){
        QSettings settings("TaskEmb", "TaskEmb");
        createNotification("Task created : " + task->getTitle(), settings.value("userID").toInt(), task->getId(), Notification::NotificationType::TaskCreated, "info");
    }else{
        // Get the list of users assigned to the task
        QList<User*> users = m_dbManager -> usersAssigned(task->getId(), nullptr);
        switch(event){
            // On task updated
            case TaskEvent::Updated:
                notifyUsers(users, task, Notification::NotificationType::TaskUpdated, "info");
                break;

            // On task deleted
            case TaskEvent::Deleted:
                notifyUsers(users, task, Notification::NotificationType::TaskDeleted, "alert");
                break;

            // On task overdue
            case TaskEvent::Overdue:
               notifyUsers(users, task, Notification::NotificationType::TaskOverdue, "alert");
                break;

            // On status task changed
            case TaskEvent::StatusChanged:
                notifyUsers(users, task, Notification::NotificationType::TaskStatusChange, "info");
                break;
        }
    }
}

/**
 * @brief NotificationManager::onTaskAssigned\
 * Notify an user that he/she is assigned to a task
 * @param task
 * @param userAssigned
 */
void NotificationManager::onTaskAssigned(const TaskPtr &task, int userAssignedId)
{
    createNotification("Task assigned : " + task->getTitle(), userAssignedId, task->getId(), Notification::NotificationType::TaskAssigned, "info");
}

/**
 * @brief NotificationManager::notifyUsers
 * Notify all users that are assignend to the task depoending on the typeEvent and level
 * If Status change -> We give the new status of the task
 * If task deleted -> We always insert the notification in database, but we give NULL to the taskId to avoid conflict with FK
 * If task overdue -> We give the datw
 * This function is responsible of lyfe cycle of Users
 * @param users
 * @param task
 * @param typeEvent
 * @param level
 * @return
 */
void NotificationManager::notifyUsers(QList<User *> &users, const TaskPtr &task, Notification::NotificationType typeEvent, const QString &level)
{
    QString notificationName(Notification::notificationTypeToString(typeEvent));
    if(typeEvent == Notification::NotificationType::TaskStatusChange) notificationName = "New Status: " + task->statusString();
    try {
        for(auto &user: users){
            int idTask = task->getId();
            if(typeEvent == Notification::NotificationType::TaskDeleted){
                idTask = 0;
            }
            if(typeEvent == Notification::NotificationType::TaskOverdue){
                createNotification("Task Overdue : " + task->getTitle() + ". Date_due : " + task->getDueDate().toString("yyyy-MM-dd hh:mm"), user->getId(), idTask, typeEvent, level);
            }else{
                createNotification(notificationName + " : " + task->getTitle(), user->getId(), idTask, typeEvent, level);
            }
            delete user;
        }
    } catch (const std::exception& e) {
        qDebug() << (QString("Error adding notification on %1 : %2")
                         .arg(notificationName)
                         .arg(e.what()));
    }
}

/**
 * @brief NotificationManager::countUnreadNotification
 * Get the count of unread Notifications of active users
 * @return
 */
int NotificationManager::countUnreadNotification()
{
    QSettings settings("TaskEmb", "TaskEmb");
    return m_dbManager-> countNotification(settings.value("userID").toInt());
}

void NotificationManager::readNotification(int notificationId)
{

    if (m_dbManager->readNotification(notificationId)){
        emit readNotificationSignal();
    }
}

NotificationManager::NotificationManager(QObject *parent)
{

}

/**
 * @brief NotificationManager::NotificationManager
 * @param dbManager
 * @param parent
 */
NotificationManager::NotificationManager(const std::shared_ptr<DatabaseManager> &dbManager, QObject *parent) : QObject(parent),
    m_dbManager(dbManager)
{}

/**
 * @brief NotificationManager::getUnreadNotifications
 * Get all notifications of the active users
 * @return
 */
QList<Notification*> NotificationManager::getUnreadNotifications(){
    QSettings settings("TaskEmb", "TaskEmb");
    qDeleteAll(m_activeNotifications);
    m_activeNotifications.clear();
    m_activeNotifications = m_dbManager->getUnreadNotifications(settings.value("userID").toInt(), this);
    return m_activeNotifications;
}
