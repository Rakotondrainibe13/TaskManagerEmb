#include "../include/database_manager.h"
#include <QSqlError>
#include <QDebug>
#include <QList>

std::shared_ptr<DatabaseManager> DatabaseManager::s_instance = nullptr;
QMutex DatabaseManager::mutex;

std::shared_ptr<DatabaseManager> DatabaseManager::instance(QObject *parent) {
	if (!s_instance) {
		mutex.lock();
		if (!s_instance) {
            s_instance = std::make_shared<DatabaseManager>(parent);
		}
		mutex.unlock();
	}
	return s_instance;
}

DatabaseManager::DatabaseManager(QObject *parent)
	: QObject(parent) {
}

bool DatabaseManager::initDatabase() {
    m_db = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
    m_db->setDatabaseName("database.db");

    if (!m_db->open()) {
        qDebug() << "Failed to open database:" << m_db->lastError().text();
		return false;
	}

    m_db->setConnectOptions("QSQLITE_ENABLE_SHARED_CACHE;QSQLITE_ENABLE_REGEXP");
    QSqlQuery query(*m_db);
    query.exec("PRAGMA profile = 'ON'");
    qDebug() << "Profilage des requêtes SQL créer";

	return true;
}

void DatabaseManager::analyzeSlowQueries() {
    qDebug() << "---------------analyzeSlowQueries-----------------";
    QSqlQuery query(*m_db);
    query.exec("PRAGMA profile");

    // Parcourir les résultats du profilage
    while (query.next()) {
        QString queryText = query.value(0).toString();  // Texte de la requête
        int executionTime = query.value(1).toInt();     // Temps d'exécution en millisecondes

        // Afficher les requêtes avec leur temps d'exécution
        if (executionTime > 100) { // Filtrer les requêtes lentes, par exemple > 100 ms
            qDebug() << "Requête SQL lente:" << queryText << "Temps:" << executionTime << "ms";
        }
    }
    qDebug() << "---------------analyzeSlowQueries-----------------";
}

bool DatabaseManager::executeNonQuery(const QString& query) {
    QMutexLocker locker(&mutex);
    QSqlQuery sqlQuery(*m_db);
    if (!sqlQuery.exec(query)) {
        qDebug() << "Query execution failed:" << sqlQuery.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::isUsersTableEmpty() {
    QString checkUserCount = R"(SELECT COUNT(*) FROM Users)";
    QSqlQuery query;
    if (query.exec(checkUserCount)) {
        if (query.next()) {
            int userCount = query.value(0).toInt();
            return (userCount == 0);
        }
    } else {
        qDebug() << "Failed to execute query:" << query.lastError();
    }
    return false;
}

bool DatabaseManager::initCreateTables(){
	// Task Table
	QString createTask = R"(
		CREATE TABLE IF NOT EXISTS Tasks (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			title VARCHAR(255) NOT NULL,
			description TEXT,
			status VARCHAR(50) NOT NULL,
			type VARCHAR(50) NOT NULL,
			priority INTEGER,
			due_date DATETIME,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            updated_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            startDateEstim DATETIME
		);
	)";
	
	//  TaskDependencies Table
	QString createTaskDependencies = R"( CREATE TABLE IF NOT EXISTS TaskDependencies (
			task_id INTEGER,
			dependency_id INTEGER,
			PRIMARY KEY (task_id, dependency_id),
			FOREIGN KEY (task_id) REFERENCES Tasks(id)
		ON DELETE CASCADE,
			FOREIGN KEY (dependency_id) REFERENCES Tasks(id)
		ON DELETE CASCADE
		);)";

	// TaskImbrication Table
	QString createTaskImbrication = R"( CREATE TABLE IF NOT EXISTS TaskImbrication  (
			task_id INTEGER,
			subtask_id INTEGER,
			PRIMARY KEY (task_id, subtask_id),
			FOREIGN KEY (task_id) REFERENCES Tasks(id)
		ON DELETE CASCADE,
			FOREIGN KEY (subtask_id) REFERENCES Tasks(id)
		ON DELETE CASCADE
		);)";

	// Users Table
	QString createUsers = R"(
        CREATE TABLE IF NOT EXISTS Users (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			username VARCHAR(50) UNIQUE NOT NULL,
			password_hash VARCHAR(255) NOT NULL,
			email VARCHAR(100) UNIQUE NOT NULL,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
			roleuser VARCHAR(50) NOT NULL DEFAULT 'r'
		);
	)";

	// TaskAssignements Table
	QString createTaskAssignments= R"(
		CREATE TABLE IF NOT EXISTS TaskAssignments (
			task_id INTEGER,
			user_id INTEGER,
			assigned_at DATETIME DEFAULT CURRENT_TIMESTAMP,
			PRIMARY KEY (task_id, user_id),
			FOREIGN KEY (task_id) REFERENCES Tasks(id) ON DELETE CASCADE,
			FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE CASCADE
		);
	)";

	// Notifications Table
	QString createNotifications = R"(
		CREATE TABLE IF NOT EXISTS Notifications (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			user_id INTEGER,
			task_id INTEGER,
			message TEXT NOT NULL,
			is_read BOOLEAN DEFAULT FALSE,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            notification_type VARCHAR(50),
			FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE CASCADE,
			FOREIGN KEY (task_id) REFERENCES Tasks(id) ON DELETE CASCADE
		);
	)";

	// TaskExecutionLogs
	QString createTaskExecutionLogs = R"(
		CREATE TABLE IF NOT EXISTS TaskExecutionLogs (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			task_id INTEGER,
			execution_strategy VARCHAR(50),
			start_time DATETIME,
			end_time DATETIME,
			status VARCHAR(50),
			FOREIGN KEY (task_id) REFERENCES Tasks(id) ON DELETE CASCADE
		);
	)";

	// SecurityLogs Table
	QString createSecurityLogs = R"(
		CREATE TABLE IF NOT EXISTS SecurityLogs (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			user_id INTEGER,
			action VARCHAR(100) NOT NULL,
			timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
			details TEXT,
			FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE SET NULL
		);
	)";

    // SubscriptionTypes table
    QString createSubscriptionTypes = R"(
        CREATE TABLE IF NOT EXISTS SubscriptionTypes (
           id INTEGER PRIMARY KEY AUTOINCREMENT,
           subscription_type_name VARCHAR(100) NOT NULL,
           price REAL NOT NULL,
           duration INTEGER NOT NULL
        );
    )";

    // Subscriptions table
    QString createSubscriptions = R"(
        CREATE TABLE IF NOT EXISTS Subscriptions (
           id INTEGER PRIMARY KEY AUTOINCREMENT,
           user_id INTEGER,
           subscription_type_id INTEGER,
           quantity INTEGER,
           start_date DATETIME NOT NULL,
           end_date DATETIME NOT NULL,
           price REAL NOT NULL,
           duration INTEGER NOT NULL,
           subscription_date DATETIME DEFAULT CURRENT_TIMESTAMP,
           status INTEGER,
           FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE SET NULL,
           FOREIGN KEY (subscription_type_id) REFERENCES SubscriptionTypes(id) ON DELETE SET NULL
        );
    )";

	QString createTasksIndex = R"(CREATE INDEX IF NOT EXISTS idx_tasks_title ON Tasks(title);)";
	QString createUsersIndex = R"(CREATE INDEX IF NOT EXISTS idx_users_infos ON Users(username, email,roleuser);)";
	QString createTaskAssignmentsIndex = R"(CREATE INDEX IF NOT EXISTS idx_taskassignments_task_user ON TaskAssignments(task_id, user_id);)";
	QString createNotificationsIndex = R"(CREATE INDEX IF NOT EXISTS idx_notifications_user_id ON Notifications(user_id);)";
	QString createTaskExecutionLogsIndex = R"(CREATE INDEX IF NOT EXISTS idx_taskexecutionlogs_task_id ON TaskExecutionLogs(task_id);)";
	QString createSecurityLogsIndex = R"(CREATE INDEX IF NOT EXISTS idx_securitylogs_user_id ON SecurityLogs(user_id);)";
    QString createSubscriptionsIndex = R"(CREATE INDEX IF NOT EXISTS idx_subscriptions_user_id ON Subscriptions(user_id);)";

	QString createUser = R"(INSERT INTO Users (username, password_hash, email, roleuser) VALUES
		('User_1', 'HRggBgcKADc=', 'user1@example.com','r'),
		('User_2', 'HRggBgcKADc=', 'user2@example.com','rw'),
		('User_3', 'HRggBgcKADc=', 'user3@example.com','ADMIN');
	)";

    QString createSubscriptionTypesData = R"(
        INSERT INTO SubscriptionTypes (id, subscription_type_name, price, duration) VALUES
        (1, 'Monthly Subscription', 20000, 30),
        (2, 'Yearly Subscription', 100000, 365);
    )";

	if(!executeNonQuery(createTask)) return false;
	if(!executeNonQuery(createTaskDependencies)) return false;
	if(!executeNonQuery(createTaskImbrication)) return false;
	if(!executeNonQuery(createUsers)) return false;
	if(!executeNonQuery(createTaskAssignments)) return false;
	if(!executeNonQuery(createNotifications)) return false;
	if(!executeNonQuery(createTaskExecutionLogs)) return false;
	if(!executeNonQuery(createSecurityLogs)) return false;

	if (!executeNonQuery(createTasksIndex)) return false;
	if (!executeNonQuery(createUsersIndex)) return false;
	if (!executeNonQuery(createTaskAssignmentsIndex)) return false;
	if (!executeNonQuery(createNotificationsIndex)) return false;
	if (!executeNonQuery(createTaskExecutionLogsIndex)) return false;
	if (!executeNonQuery(createSecurityLogsIndex)) return false;

    if (!executeNonQuery(createSubscriptionTypes)) return false;
    if (!executeNonQuery(createSubscriptions)) return false;
    if (!executeNonQuery(createSubscriptionsIndex)) return false;

    if (isUsersTableEmpty()){
        if (!executeNonQuery(createUser)) return false;
    }

    if (isSubscriptionTypesTableEmpty()) {
        if (!executeNonQuery(createSubscriptionTypesData)) return false;
    }


	return true;
}

bool DatabaseManager::updateTask(const TaskPtr& task){
	try {
        QSqlQuery query(*m_db);
        query.prepare(R"(
            UPDATE Tasks SET title=:title, description=:description, type=:type, priority=:priority, due_date=:due_date, status=:status WHERE id=:id
        )");

        query.bindValue(":title", task->getTitle());
        query.bindValue(":description", task->getDescription());
        query.bindValue(":type", task->getType());
        query.bindValue(":due_date", task->getDueDate().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":id", task->getId());

        int priorityInt = static_cast<int>(task->getPriority());
        QString status = QString::number(static_cast<int>(task->getStatus()));

        query.bindValue(":priority", priorityInt);
        query.bindValue(":status", status);

        if (!query.exec()) {
            qWarning() << "Failed to execute query:" << query.lastError().text();
			return false;
        }

    } catch (...) {
		    qWarning() << "An unknown exception occurred.";
        return false;
    }
    qDebug() << "Task updated";
    return true;
}

bool DatabaseManager::deleteTask(const int taskId)
{
    try {
        QSqlQuery query(*m_db);

        // Enable foreign key constraints in order to delete task on casade
        if (!query.exec("PRAGMA foreign_keys = ON;")) {
            qWarning() << "Failed to enable foreign key constraints:" << query.lastError().text();
            return false;
        }

        query.prepare(R"(
            DELETE FROM Tasks WHERE id=:id
        )");

        query.bindValue(":id", taskId);

        if (!query.exec()) {
            qWarning() << "Failed to execute query:" << query.lastError().text();
            return false;
        }

    } catch (...) {
        qWarning() << "An unknown exception occurred.";
        return false;
    }
    qDebug() << "Task removed";
    return true;
}

bool DatabaseManager::saveTask(const TaskPtr& tasks)
{
    try {
        QSqlQuery query(*m_db);

        query.prepare(R"(
            INSERT INTO Tasks (title, description, status, type, priority, due_date)
            VALUES (:title, :description, :status, :type, :priority, :due_date) returning id
        )");

        int priorityInt = static_cast<int>(tasks->getPriority());

        // Bind values to placeholders
        query.bindValue(":title", tasks->getTitle());
        query.bindValue(":description", tasks->getDescription());
        query.bindValue(":status", "0");
        query.bindValue(":type", tasks->getType());
        query.bindValue(":priority", priorityInt);
        query.bindValue(":due_date", tasks->getDueDate().toString("yyyy-MM-dd HH:mm:ss")); // Format for DATETIME


        if (!query.exec()) {
            // Log or handle query execution error
            qDebug() << "Failed to execute query:" << query.lastError().text();
            return false;
        }

    } catch (const std::exception& e) {
        qDebug() << (QString("Error creating task: %1").arg(e.what()));
        return false;
    }
    return true;
}

/**
 * @brief DatabaseManager::saveTaskGetId
 * Save the task in database and get the reterning id
 * @param tasks
 * @return
 */
int DatabaseManager::saveTaskGetId(const TaskPtr &tasks)
{
    try {
        QSqlQuery query(*m_db);

        query.prepare(R"(
            INSERT INTO Tasks (title, description, status, type, priority, due_date)
            VALUES (:title, :description, :status, :type, :priority, :due_date) returning id
        )");

        int priorityInt = static_cast<int>(tasks->getPriority());

        // Bind values to placeholders
        query.bindValue(":title", tasks->getTitle());
        query.bindValue(":description", tasks->getDescription());
        query.bindValue(":status", "0");
        query.bindValue(":type", tasks->getType());
        query.bindValue(":priority", priorityInt);
        query.bindValue(":due_date", tasks->getDueDate().toString("yyyy-MM-dd HH:mm:ss")); // Format for DATETIME


        if (!query.exec()) {
            // Log or handle query execution error
            qDebug() << "Failed to execute query:" << query.lastError().text();
            return 0;
        }
        query.next();
        return query.value(0).toInt();

    } catch (const std::exception& e) {
        qDebug() << (QString("Error creating task: %1").arg(e.what()));
        return 0;
    }
}

bool DatabaseManager::removeSubtask(const int parentTaskId, const int subtaskId){
    try{
        QSqlQuery query(*m_db);
        query.prepare(R"(
            DELETE FROM TaskImbrication where task_id=:taskId and subtask_id=:subtaskId
        )");

        query.bindValue(":taskId", parentTaskId);
        query.bindValue(":subtaskId", subtaskId);

        if (!query.exec()) {
            // Log or handle query execution error
            qDebug() << "Failed to execute query:" << query.lastError().text();
            return false;
        }

    }catch(const std::exception& e){
        qDebug() << (QString("Error removing subtask: %1").arg(e.what()));
        return false;
    }

    return true;
}

bool DatabaseManager::addSubtask(const int parentTaskId, const int subtaskId){
    try{
        QSqlQuery query(*m_db);
        query.prepare(R"(
            insert into TaskImbrication(task_id,subtask_id) values (:taskId,:subtaskId)
        )");

        query.bindValue(":taskId", parentTaskId);
        query.bindValue(":subtaskId", subtaskId);

        if (!query.exec()) {
            // Log or handle query execution error
            qDebug() << "Failed to execute query:" << query.lastError().text();
            return false;
        }

    }catch(const std::exception& e){
        qDebug() << (QString("Error adding subtask: %1").arg(e.what()));
        return false;
    }

    return true;
}

std::shared_ptr<QSqlDatabase> DatabaseManager::getDatabase(){
	return m_db;
}

bool DatabaseManager::updateUserRole(const int userID, const QString role){
    try {
        QSqlQuery query(*m_db);
        query.prepare(R"(
            UPDATE Users SET roleuser=:roleuser WHERE id=:id
        )");

        query.bindValue(":roleuser", role);
        query.bindValue(":id", userID);

        if (!query.exec()) {
            qWarning() << "Failed to execute query:" << query.lastError().text();
            return false;
        }

    } catch (...) {
        qWarning() << "An unknown exception occurred.";
        return false;
    }
    qDebug() << "User updated";
    return true;
}

/**
 * @brief DatabaseManager::usersAssigned
 * Get a list of user assigned to a task, and giving the parent as life cycle
 * @param taskId
 * @param parent
 * @return
 */
QList<User*> DatabaseManager::usersAssigned(int taskId, QObject* parent)
{
    QList<UserPtr> result;
    try {
        QSqlQuery query(*m_db);
        query.prepare(R"(
            SELECT
                ta.task_id,
                u.id,
                u.username
            from TaskAssignments ta
            join Users u on u.id = ta.user_id
            where ta.task_id = :taskId
        )");
        query.bindValue(":taskId", taskId);

        if (!query.exec()) {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
        while (query.next()) {
            User* temp = new User(query.value("id").toInt(), query.value("username").toString(), parent);
            result.append(temp);
        }
    } catch (const std::exception& e) {
        qWarning() << "An unknown exception occurred on getting all uiser assigned to a taskid " << taskId;
    }
    return result;
}

/**
 * @brief DatabaseManager::usersNotAssigned
 * Usefull in QML, those are list of users that are not assignend to a specific task
 * @param taskId
 * @param parent
 * @return
 */
QList<User *> DatabaseManager::usersNotAssigned(int taskId, QObject *parent)
{
    QList<UserPtr> result;
    try {
        QSqlQuery query(*m_db);
        query.prepare(R"(
            SELECT
                u.username,
                u.id,
                t1.idtask
            FROM
                (
                    SELECT
                        t.id AS idtask,
                        u.id AS iduser
                    FROM
                        Users u
                    RIGHT JOIN
                        Tasks t
                    EXCEPT
                    SELECT
                        ta.task_id,
                        ta.user_id
                    FROM
                        TaskAssignments ta
                ) AS t1
            JOIN
                Users u
            ON
                u.id = t1.iduser
            WHERE idtask = :taskId
        )");
        query.bindValue(":taskId", taskId);

        if (!query.exec()) {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
        while (query.next()) {
            User* temp = new User(query.value("id").toInt(), query.value("username").toString(), parent);
            result.append(temp);
        }
    } catch (const std::exception& e) {
        qWarning() << "An unknown exception occurred on getting all users not assigned to a taskid " << taskId;
    }
    return result;
}

bool DatabaseManager::deleteUserAssigned(const int &userId, const int &taskId)
{
    try{
        QSqlQuery query(*m_db);
        query.prepare(R"(
            DELETE FROM TaskAssignments where task_id=:taskId and user_id=:userId
        )");

        query.bindValue(":taskId", taskId);
        query.bindValue(":userId", userId);

        if (!query.exec()) {
            // Log or handle query execution error
            qDebug() << "Failed to execute query:" << query.lastError().text();
            return false;
        }

    }catch(const std::exception& e){
        qDebug() << (QString("Error removing users assignment from tasks: %1").arg(e.what()));
        return false;
    }

    return true;
}

bool DatabaseManager::addUserAssigned(const int &taskId, const int &userId, QSqlQuery *query)
{

    if(query){
        try{
            query->prepare(R"(
            insert into TaskAssignments(task_id,user_id) values (:taskId,:userId)
        )");

            query->bindValue(":taskId", taskId);
            query->bindValue(":userId", userId);

            if (!query->exec()) {
                // Log or handle query execution error
                qDebug() << "Failed to execute query:" << query->lastError().text();
                return false;
            }

        }catch(const std::exception& e){
            qDebug() << (QString("Error adding User assignment: %1").arg(e.what()));
            return false;
        }
        return true;
    }
    return false;
}


/**
 * @brief save notification in database
 * @param notification
 * @return
 */
bool DatabaseManager::saveNotification(const Notification* notification)
{
    if(notification){
        try{
            QSqlQuery query(*m_db);
            query.prepare(R"(
                insert into Notifications(user_id, task_id, message, is_read, notification_type)
                values
                (:user_id, :task_id, :message, :is_read, :notification_type)
            )");

            query.bindValue(":user_id", notification->userId());
            query.bindValue(":task_id", notification->taskId() != 0 ? notification->taskId() : QVariant(QVariant::Int));
            query.bindValue(":message", notification->message());
            query.bindValue(":is_read", notification->isRead());
            query.bindValue(":notification_type", Notification::notificationTypeToString(notification->type()));

            if (!query.exec()) {
                // Log or handle query execution error
                qDebug() << "Failed to execute query:" << query.lastError().text();
                return false;
            }
            return true;
        }catch(const QSqlError& error){
            qDebug() << (QString("Error adding notification: %1").arg(error.databaseText()));
        }
    }
}

/**
 * @brief read notification 
 * @param notificationId
 * @return 
 */
 
bool DatabaseManager::readNotification(int notificationId){
    if (notificationId)
    {
        try
        {
            QSqlQuery query(*m_db);
            query.prepare(R"(UPDATE Notifications set is_read = 1 where id = :id)");
            query.bindValue(":id",notificationId);
            if (!query.exec())
            {
                qWarning() << "dbmanager::readNotification - Failed to execute query:" << query.lastError().text();
			    return false;
            }
        }
        catch (const std::exception& ex)
        {   
            qWarning() << "error occured readNotification : " << ex.what();
            return false;
        }
        qDebug() << "readNotification successful!";
        return true;
    } 
    qWarning() << "NotificationId invalid : " << notificationId;  
    return false;
}

/**
 * @brief remove notification 
 * @param notificationId
 * @return 
 */

bool DatabaseManager::removeNotification(int notificationId){
    if (notificationId)
    {
        try
        {
            QSqlQuery query(*m_db);
            query.prepare(R"(DELETE FROM Notifications WHERE id = :id)");
            query.bindValue(":id",notificationId);
            if (!query.exec())
            {
                qWarning() << "dbmanager::removeNotification - Failed to execute query:" << query.lastError().text();
			    qDebug() << "query : " << query.executedQuery();
                return false;
            }
        }
        catch (const std::exception& ex)
        {
            qWarning() << "error occured removeNotification : " << ex.what();
            return false;   
        }
        qDebug() << "removeNotification successful!";
        return true;
    }
    qWarning() << "NotificationId invalid : " << notificationId;  
    return false;
}

/**
 * @brief get unread notification 
 * @param userId
 * @return 
 */

QList<Notification*> DatabaseManager::getUnreadNotifications(int userId, QObject* parent){

    QList<Notification*> unreadList;
    if (userId)
    {
        try
        {    
            QSqlQuery query(*m_db);
            // query.prepare(R"(
            //     SELECT
            //         n.*,
            //         t.priority
            //     FROM Notifications n
            //     JOIN Tasks t ON t.id = n.task_id
            //     WHERE is_read = 0
            //     AND user_id = :userId
            //     ORDER BY t.priority DESC, n.created_at DESC
            // )");

            query.prepare(R"(
                SELECT
                    n.*
                FROM Notifications n
                WHERE is_read = 0
                AND user_id = :userId
                ORDER BY n.created_at DESC
            )");
            query.bindValue(":userId", userId);
            if (query.exec())
            {
                while (query.next())
                {
                    int notificationId(query.value("id").toInt());
                    int taskId(query.value("task_id").toInt());
                    QString message(query.value("message").toString());
                    bool isRead(query.value("is_read").toBool());
                    QString strType(query.value("notification_type").toString());
                    Notification::NotificationType type = Notification::StringToNotificationType(strType);

                    unreadList.append(new Notification(notificationId, userId, taskId, message, isRead, type,parent));
                }
            }
        }
        catch (const std::exception& ex)
        {
            qWarning() << "error occured dbmanager::getUnreadNotifications ->  "<< ex.what();
        }
    }
    return unreadList;
}

/**
 * @brief DatabaseManager::countNotification
 * Count the unread notification of active users
 * @return
 */
int DatabaseManager::countNotification(int userId)
{
    try {
        QSqlQuery query(*m_db);
        query.prepare(R"(
            SELECT count() AS total
            FROM Notifications
            WHERE user_id = :userId
            AND is_read = 0
        )");
        query.bindValue(":userId", userId);

        if (!query.exec()) {
            qWarning() << "Failed to execute query:" << query.lastError().text();
            return 0;
        }
        query.next();
        return query.value(0).toInt();

    } catch (const std::exception& e) {
        qWarning() << "An unknown exception occurred on counting the notification of users.";
        return 0;
    }
}

bool DatabaseManager::saveSubscription(const SubscriptionPtr& subscription)
{
    try {
        QSqlQuery query(*m_db);

        query.prepare(R"(
            INSERT INTO Subscriptions (user_id, subscription_type_id, quantity, start_date, end_date, price, duration, subscription_date, status)
            VALUES (:user_id, :subscription_type_id, :quantity, :start_date, :end_date, :price, :duration, :subscription_date, :status)
        )");

        query.bindValue(":user_id", subscription->userId());
        query.bindValue(":subscription_type_id", subscription->subscriptionType()->id());
        query.bindValue(":quantity", subscription->quantity());
        query.bindValue(":start_date", subscription->startDate().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":end_date", subscription->endDate().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":price", subscription->price());
        query.bindValue(":duration", subscription->duration());
        query.bindValue(":subscription_date", subscription->subscriptionDate().toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":status", "1");

        if (!query.exec()) {
            qDebug() << "Failed to execute query :" << query.lastError().text();
            return false;
        }

        QVariant lastId = query.lastInsertId();
        subscription->setId(lastId.toInt());


        return true;
    } catch (const std::exception& e) {
        qDebug() << (QString("Error creating subscription %1").arg(e.what()));
        return false;

    }
}

bool DatabaseManager::isSubscriptionTypesTableEmpty()
{
    QString subscriptionTypesCountQuery = "SELECT count(*) FROM SubscriptionTypes";
    QSqlQuery query(*m_db);
    if (query.exec(subscriptionTypesCountQuery)) {
        if (query.next()) {
            int subscriptionTypesCount = query.value(0).toInt();
            return (subscriptionTypesCount == 0);
        }
    } else {
        qDebug() << "Failed to execute query: " << query.lastError();
    }

    return false;
}
