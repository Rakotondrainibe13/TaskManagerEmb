#include "notification.h"

Notification::Notification(QObject *parent)
    : QObject{parent}
{}

Notification::Notification(int userId, int taskId, const QString &message, bool isRead, NotificationType type, QObject *parent)
: QObject{parent}
{
    setUserId(userId);
    setTaskId(taskId);
    setMessage(message);
    setIsRead(isRead);   
    setType(type);
}

Notification::Notification(int notificationId, int userId, int taskId, const QString &message, bool isRead, NotificationType type, QObject *parent): QObject{parent}
{
    setUserId(userId);
    setTaskId(taskId);
    setMessage(message);
    setIsRead(isRead);
    setType(type);
    setId(notificationId);
}


/**
 * @brief A function that return ths string value of a notificatio type
 * @param type
 * @return
 */
QString Notification::notificationTypeToString(NotificationType type)
{
    switch (type) {
        case NotificationType::TaskCreated:
            return "Task Created";
        case NotificationType::TaskUpdated:
            return "Task Updated";
        case NotificationType::TaskDeleted:
            return "Task Deleted";
        case NotificationType::TaskOverdue:
            return "Task Overdue";
        case NotificationType::TaskStatusChange:
            return "Task Status Changed";
        case NotificationType::TaskAssigned:
            return "Task Assigned";
        default:
            return "Unknown Notification Type";
    }
}
Notification::NotificationType Notification::StringToNotificationType(const QString &strType) {
    if (strType == "Task Created")
        return Notification::NotificationType::TaskCreated;
    else if (strType == "Task Updated")
        return Notification::NotificationType::TaskUpdated;
    else if (strType == "Task Deleted")
        return Notification::NotificationType::TaskDeleted;
    else if (strType == "Task Overdue")
        return Notification::NotificationType::TaskOverdue;
    else if (strType == "Task Status Changed")
        return Notification::NotificationType::TaskStatusChange;
    else if (strType == "Task Assigned")
        return Notification::NotificationType::TaskAssigned;
    else
        return Notification::NotificationType::TaskCreated; // Default case
}


int Notification::id() const
{
    return m_id;
}

void Notification::setId(int newId)
{
    m_id = newId;
}

int Notification::userId() const
{
    return m_userId;
}

void Notification::setUserId(int newUserId)
{
    m_userId = newUserId;
}

int Notification::taskId() const
{
    return m_taskId;
}

void Notification::setTaskId(int newTaskId)
{
    m_taskId = newTaskId;
}

bool Notification::isRead() const
{
    return m_isRead;
}

void Notification::setIsRead(bool newIsRead)
{
    m_isRead = newIsRead;
}

QDateTime Notification::createdAt() const
{
    return m_createdAt;
}

void Notification::setCreatedAt(const QDateTime &newCreatedAt)
{
    m_createdAt = newCreatedAt;
}

QString Notification::message() const
{
    return m_message;
}

void Notification::setMessage(const QString &newMessage)
{
    m_message = newMessage;
}

Notification::NotificationType Notification::type() const
{
    return m_type;
}

void Notification::setType(NotificationType newType)
{
    m_type = newType;
}

QString Notification::notificationString()
{
    return notificationTypeToString(this->type());
}

// Notification::Notification(int userId, int taskId, const QString &message, bool isRead, Notification::NotificationType type, QObject *parent) : QObject(parent),
//     m_userId(userId),
//     m_taskId(taskId),
//     m_message(message),
//     m_isRead(isRead),
//     m_type(type)
// {}
