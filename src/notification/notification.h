#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include <QDateTime>

class Notification : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int taskId READ taskId CONSTANT)
    Q_PROPERTY(QString message READ message CONSTANT)
    Q_PROPERTY(QString level READ notificationString CONSTANT)
public:

    enum class NotificationType{
        TaskCreated = 1,
        TaskUpdated = 2,
        TaskDeleted = 3,
        TaskOverdue = 4,
        TaskStatusChange = 5,
        TaskAssigned = 6
    };

    explicit Notification(QObject *parent = nullptr);
    Notification(int userId, int taskId, const QString &message, bool isRead, NotificationType type, QObject *parent = nullptr);
    Notification(int notificationId, int userId, int taskId, const QString &message, bool isRead, NotificationType type, QObject *parent = nullptr);

    static QString notificationTypeToString(NotificationType type);
    static NotificationType StringToNotificationType(const QString &strType);
    // Getters and setters
    int id() const;
    void setId(int newId);

    int userId() const;
    void setUserId(int newUserId);

    int taskId() const;
    void setTaskId(int newTaskId);

    bool isRead() const;
    void setIsRead(bool newIsRead);

    QDateTime createdAt() const;
    void setCreatedAt(const QDateTime &newCreatedAt);

    QString message() const;
    void setMessage(const QString &newMessage);

    NotificationType type() const;
    void setType(NotificationType newType);

    QString notificationString();

signals:

private:
    int m_id;
    int m_userId;
    int m_taskId;
    QString m_message;
    bool m_isRead;
    QDateTime m_createdAt;
    NotificationType m_type;
};

#endif // NOTIFICATION_H
