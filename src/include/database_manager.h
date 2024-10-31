#pragma once

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMutex>
#include <QSharedPointer>

#include "task.h"
#include "../notification/notification.h"
#include "subscription.h"


class DatabaseManager : public QObject {
	Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    static std::shared_ptr<DatabaseManager> instance(QObject *parent = nullptr);
	bool initDatabase();
	bool initCreateTables();
    bool removeSubtask(const int parentTaskId, const int subtaskId);
    bool addSubtask(const int parentTaskId, const int subtaskId);
    bool saveTask(const TaskPtr& tasks);
    int saveTaskGetId(const TaskPtr& tasks);
	bool isUsersTableEmpty();
	bool executeNonQuery(const QString& query);

	template <typename Mapper>
    bool executeSelectQuery(const QString& query, Mapper& mapper);

    bool updateTask(const TaskPtr& task);
    bool deleteTask(const int taskId);
    std::shared_ptr<QSqlDatabase> getDatabase();
    bool updateUserRole(const int userId,const QString role);

    QList<User*> usersAssigned(int taskId, QObject* parent);
    QList<User*> usersNotAssigned(int taskId, QObject* parent);
    bool deleteUserAssigned(const int& userId, const int& taskId);
    bool addUserAssigned(const int&taskId , const int& userId, QSqlQuery *query);

    // Notification section
    bool saveNotification(const Notification* notification);
    bool readNotification(int notificationId);
    bool removeNotification(int notificationId);
    QList<Notification*> getUnreadNotifications(int userId, QObject* parent);

    int countNotification(int userId);

    bool saveSubscription(const SubscriptionPtr& subscription);
    bool isSubscriptionTypesTableEmpty();


    void analyzeSlowQueries();
private:
    static std::shared_ptr<DatabaseManager> s_instance;
    std::shared_ptr<QSqlDatabase> m_db;
	static QMutex mutex;
};

template <typename Mapper>
bool DatabaseManager::executeSelectQuery(const QString& query, Mapper& mapper) {
	QMutexLocker locker(&mutex);
    QSqlQuery sqlQuery(*m_db);
	if (!sqlQuery.exec(query)) {
		qDebug() << "Query execution failed:" << sqlQuery.lastError().text();
		return false;
	}
	while (sqlQuery.next()) {
		mapper.map(sqlQuery);
	}
	return true;
}
