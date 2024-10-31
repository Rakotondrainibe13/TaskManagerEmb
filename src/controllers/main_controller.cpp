#include <QDebug>
#include "../controllers/main_controller.h"
#include "../include/task_manager.h"
#include "../include/security_manager.h"
#include "../include/network_manager.h"
#include "../include/task_factory.h"
#include "../include/task.h"
#include "../include/database_manager.h"
#include "../include/task_mapper.h"
#include <vector>
#include <memory>
#include <iostream>
#include <QTcpSocket>
#include "../include/aesencryption_strategy.h"
#include "../include/notification_manager.h"
#include "../include/authorization_manager.h"
#include "../include/synch_manager.h"
#include "../include/ssh_manager.h"
#include "../include/exception_manager.h"

namespace controllers
{
    MainController::MainController(QObject *parent)
        : QObject(parent), m_tasks(QList<Task *>())
    {
        m_navigationController = std::make_unique<NavigationController>(this);
        m_dbManager = DatabaseManager::instance();
        m_securityManager = std::make_unique<SecurityManager>(this);
        m_taskFactory = std::make_shared<TaskFactory>(this);
        m_taskManager = std::make_unique<TaskManager>(m_taskFactory, m_dbManager, this);
        m_taskManager->registerObserver(&NotificationManager::getInstance(m_dbManager, this));
        m_authorizationManager = std::make_unique<AuthorizationManager>(this);
        m_userManager = std::make_unique<UserManager>(m_dbManager, this);
        m_formValidator = std::make_unique<FormValidator>(this);
        m_synchManager = SynchManager::getInstance();
        m_subscriptionManager = std::make_shared<SubscriptionManager>(m_dbManager, this);
        m_taskManager->setSubscriptionManager(m_subscriptionManager);
        m_subscriptionManager = std::make_shared<SubscriptionManager>(m_dbManager, this);
        m_taskManager->setSubscriptionManager(m_subscriptionManager);
        m_synchManager = SynchManager::getInstance();
        m_threadPool.setMaxThreadCount(QThread::idealThreadCount());
        m_taskListModel = new TaskListModel(m_taskManager.get(), this);
        connectManagers();
        this->firstInitDb();

        // Prendre tous les types d'abonnements
        m_subscriptionManager->getAllSubscriptionTypes();
        m_statistic = m_taskManager->calculateStatistics();
        generateReport();

        // QList<TaskPtr> test= getAllTasks();
        // for(const auto task : test){
        //     qDebug() << task->getTitle() << task->getId();
        // }

        // testSecurityFunctions();
        //  loadTasks();


    }

    MainController::~MainController() {
        qDeleteAll(m_tasks);
        m_tasks.clear();
        m_dbManager->analyzeSlowQueries();
        delete m_taskListModel;
    }

    TaskListModel * MainController::taskListModel() const {
        return m_taskListModel;
    }

    void MainController::firstInitDb()
    {
        if (m_dbManager->initDatabase())
        {
            qDebug() << "Database initialization success!";
            if (m_dbManager->initCreateTables())
            {
                qDebug() << "Table created successfully!";
            }
            else
            {
                qDebug() << "Table created failed!";
            }
        }
        else
        {
            qDebug() << "Database initialization failed!";
        }
    }

    void MainController::createTaskAsync(const QString& title, const QString& description, int priority, const QString& dueDate, int type)
    {
        QtConcurrent::run(&m_threadPool, [this, title, description, priority,dueDate, type](){
            createTask(title, description, priority, dueDate, type);
            QMetaObject::invokeMethod(m_taskListModel, "updateTasks", Qt::QueuedConnection);
        });
    }

    void MainController::updateTaskAsync(int taskId, const QString &title, const QString &description, int priority, const QString &dueDate) {
        QtConcurrent::run(&m_threadPool, [this, taskId, title, description, dueDate, priority]() {
            bool result = updateTask(taskId, title, description, priority, dueDate);
            QMetaObject::invokeMethod(m_taskListModel, "updateTasks", Qt::QueuedConnection);
            emit taskUpdated(result);
        });
    }

    bool MainController::assignmentTaskUserAsync(const int &taskId, const QList<int> idUsers) {

        QFuture<bool> future = QtConcurrent::run(&m_threadPool, [this, taskId, idUsers]() {
            bool result = false;
            result = assignmentTaskUser(taskId, idUsers);
            QMetaObject::invokeMethod(m_taskListModel, "updateTasks", Qt::QueuedConnection);
            return result;
        });
        return future.result();
    }

    void MainController::deleteTaskAsync(int taskId){
        QtConcurrent::run(&m_threadPool, [this, taskId]() {
            deleteTask(taskId);
            QMetaObject::invokeMethod(m_taskListModel, "updateTasks", Qt::QueuedConnection);
        });
    }
    void MainController::connectManagers()
    {
        connect(m_taskManager.get(), &TaskManager::taskAdded, this, &MainController::onTaskCreated);
        connect(m_taskManager.get(), &TaskManager::taskUpdated, this, &MainController::onTaskUpdated);
        connect(m_taskManager.get(), &TaskManager::taskRemoved, this, &MainController::onTaskDeleted);
        // connect(m_securityManager, &SecurityManager::securityEvent, this, &MainController::onSecurityEvent);
        // connect(m_networkManager, &NetworkManager::networkStatusChanged, this, &MainController::onNetworkStatusChanged);

        // connect(m_taskManager, &NotificationManager::creatingNotification, this, &MainController::handleInternalNotification);
        // Dans le constructeur de MainController
        connect(&NotificationManager::getInstance(m_dbManager, this), &NotificationManager::creatingNotification, this, &MainController::countNotificationChanged);
        connect(&NotificationManager::getInstance(m_dbManager, this), &NotificationManager::creatingNotification, this, &MainController::unreadNotificationChanged);

        connect(&NotificationManager::getInstance(m_dbManager, this), &NotificationManager::readNotificationSignal, this, &MainController::countNotificationChanged);
        connect(&NotificationManager::getInstance(m_dbManager, this), &NotificationManager::readNotificationSignal, this, &MainController::unreadNotificationChanged);

        connect(m_securityManager.get(), &SecurityManager::userConnected, this, &MainController::countNotificationChanged);
        connect(m_taskManager.get(), &TaskManager::updatedTaskSignal, this, &MainController::getTaskPtrById);

        connect(m_taskManager.get(), &TaskManager::userAssignmentChanged, this, &MainController::updateUsersAssignment);
    }

    // void MainController::loadTasks() {
    //     QList<TaskPtr> tasks = m_taskManager->getAllTasks();
    //     m_taskManager->setTasks(tasks);
    // }

    QList<Task *> MainController::getAllTasks()
    {
        QList<TaskPtr> t = m_taskManager->getAllTasks();
        // qDeleteAll(m_tasks);
        m_tasks.clear();
        for (const TaskPtr &task : t)
        {
            Task *tache = new Task();
            tache->setId(task->getId());
            tache->setTitle(task->getTitle());
            tache->setCreatedAt(task->getDueDate());
            tache->setPriority(task->getPriority());
            tache->setCreatedAt(task->getCreatedAt());
            tache->setStatus(task->getStatus());
            tache->setDescription(task->getDescription());
            tache->setDueDate(task->getDueDate());
            tache->setType(task->getType());
            m_tasks.append(tache);
        }
        return m_tasks;
    }

    void MainController::initTasks()
    {
        /*QList<TaskPtr> t = m_taskManager->getAllTasks();
        m_tasks.clear();
        for (const TaskPtr &task : t)
        {
            Task *tache = new Task();
            tache->setId(task->getId());
            tache->setTitle(task->getTitle());
            tache->setCreatedAt(task->getDueDate());
            tache->setPriority(task->getPriority());
            tache->setCreatedAt(task->getCreatedAt());
            tache->setStatus(task->getStatus());
            tache->setDescription(task->getDescription());
            tache->setDueDate(task->getDueDate());
            tache->setType(task->getType());
            m_tasks.append(tache);
        }
        return m_tasks;*/
        auto tasks = m_taskIterator->next();
        emitTasksChanged(tasks);
    }

    TaskPtr MainController::getTaskById(const int id) const
    {
        return m_taskManager->getTask(id);
    }

    void MainController::onTaskCreated(TaskPtr task)
    {
        generateReport();
        m_statistic = m_taskManager->calculateStatistics();
        qDebug() << "Task created:" << task->getTitle();
    }

    void MainController::onTaskUpdated(TaskPtr task)
    {
        qDebug() << "Task updated:" << task->getTitle();
    }

    void MainController::onTaskDeleted(int taskId)
    {
        generateReport();
        m_statistic = m_taskManager->calculateStatistics();
        qDebug() << "Task deleted:" << taskId;
    }

    void MainController::onSecurityEvent(const QString &event)
    {
        qDebug() << "Security event:" << event;
    }

    void MainController::onNetworkStatusChanged(bool isConnected)
    {
        qDebug() << "Network status changed. Connected:" << isConnected;
    }

    NavigationController *MainController::navigationController()
    {
        return m_navigationController.get();
    }

    TaskManager *MainController::taskManager()
    {
        return m_taskManager.get();
    }

    FormValidator *MainController::formValidator()
    {
        return m_formValidator.get();
    }

    SynchManager *MainController::synchManager()
    {
        return m_synchManager.get();
    }
    // QQmlListProperty<Task> MainController::tasksProperty()
    // {
    //     return QQmlListProperty<Task>(this, m_taskManager->getAllTasks());
    // }

    // bool MainController::isLoggedIn() const
    // {
    //     return m_securityManager->isLoggedIn();
    // }

    void MainController::createTask(const QString &title, const QString &description, int priority, const QString &dueDate, int type)
    {
        try
        {
            qDebug() << "Title " << title << "description " << description << " Due Date " << dueDate;
            const QDateTime dueDateTime = QDateTime::fromString(dueDate, "dd/MM/yyyy HH:mm");
            if (m_formValidator->validateTaskCreate(title, description, dueDateTime))
            {
                qDebug() << "miditra ";
                TaskPtr newTask = m_taskManager->createTask(title, description, priority, dueDateTime, type);
                if (newTask)
                {
                    emit m_taskManager->taskAdded(newTask);

                    emit tasksChanged();
                    qDebug() << "emit taskAdded";
                    emit ui_taskCreated();
                }
            }
        }
        catch (const std::exception &e)
        {
            emit errorOccurred(QString("Error creating task: %1").arg(e.what()));
        }
    }

        bool MainController::updateTask(int taskId, const QString &title, const QString &description, int priority, const QString &dueDate)
        {
            try
            {
                const QDateTime dueDateTime = QDateTime::fromString(dueDate, "dd/MM/yyyy HH:mm");
                TaskPtr updatedTask = std::make_shared<Task>(title, static_cast<Task::Priority>(priority));
                if (updatedTask)
                {
                    updatedTask->setId(taskId);
                    updatedTask->setTitle(title);
                    updatedTask->setDescription(description);
                    updatedTask->setDueDate(dueDateTime);
                    // updatedTask->setStatus(static_cast<Task::Status>(status));

                    auto result = m_taskManager->updateTask(updatedTask);
                    emit m_taskManager->taskUpdated(updatedTask);
                    if(result){
                        return result;
                    }
                }
            }
            catch (const std::exception &e)
            {
                emit errorOccurred(QString("Error updating task: %1").arg(e.what()));
            }
            return false;
        }

        void MainController::deleteTask(int taskId)
        {
            try
            {
                m_taskManager->removeTask(taskId);
                emit m_taskManager->taskRemoved(taskId);
            }
            catch (const std::exception &e)
            {
                emit errorOccurred(QString("Error deleting task: %1").arg(e.what()));
            }
        }

        void MainController::login(const QString &email, const QString &password)
        {
            qDebug() << "Email : " << email << "Password : " << password;
            if (m_formValidator->validateEmailFormText(email) && m_formValidator->validatePasswordFormText(password))
            {
                auto aesStrategy = std::make_unique<AESEncryptionStrategy>();
                m_securityManager->setEncryptionStrategy(std::move(aesStrategy));
                bool success = m_securityManager->authenticate(email, password);
                qDebug() << "Email : " << success;
                // if (success)
                // {
                    // loadTasks();
                    //  emit loginStatusChanged();
                    m_subscriptionManager->initSubscriptionManager();
                    m_navigationController->goListTaskScreen();
                // }
            }
        }

        // void MainController::createNotification(const QString &message, const QString &level)
        // {
        //     // m_notificationManager->createNotification(message, level);
        //     // m_notificationManager.createNotification(message, level);
        //     // emit notificationCreated(message, level);
        //     qDebug() << "Notification created ";
        // }

        // void MainController::handleInternalNotification(const QString &message, const QString &level)
        // {
        //     emit notificationCreated(message, level);
        //     qDebug() << "Notification created ";
        // }

        void MainController::logout()
        {
            m_securityManager->logout();
            // m_taskManager->clearTasks();
            emit tasksChanged();
            emit loginStatusChanged();
            this->m_navigationController->goLoginScreen();
        }

        bool MainController::hasAccess(const QString &resource) const
        {
            return m_authorizationManager->hasAccess(resource);
        }

        /**
         * @brief MainController::getTaskPtrById
         * Get task by id
         * @param id
         * @return
         */
        Task *MainController::getTaskPtrById(const int &id)
        {
            try {
                std::shared_ptr<Task> task = m_taskManager->getTask(id);
                Task* tache = new Task(this);
                tache->setId(task->getId());
                tache->setTitle(task->getTitle());
                tache->setCreatedAt(task->getDueDate());
                tache->setPriority(task->getPriority());
                tache->setCreatedAt(task->getCreatedAt());
                tache->setStatus(task->getStatus());
                tache->setDescription(task->getDescription());
                tache->setDueDate(task->getDueDate());
                tache->setType(task->getType());

                return tache;

            } catch (const std::exception &e) {
                qDebug() << "Exception occurred in getting the task by id: " << e.what();
            }
        }

        QList<UserPtr> MainController::getAllUsers() const
        {
            return m_userManager->getAllUsers();
        }

        QList<UserPtr> MainController::getUsersAssignedTask(const int &taskId)
        {
            return m_taskManager->usersAssigned(taskId);
        }

        QList<UserPtr> MainController::getUsersNotAssignedTask(const int &taskId)
        {
            return m_taskManager->usersNotAssigned(taskId);
        }

        bool MainController::unassignmentTaskUser(const int &taskId, const int &userId)
        {
            bool result = false;
            try
            {
                TaskPtr taskToUPdate = getTaskById(taskId);
                if(taskToUPdate){
                    result = m_taskManager->unassignmentUser(taskId, userId);
                    if(result){
                        emit m_taskManager->taskUpdated(taskToUPdate);
                        return result;
                    }

                }
            }
            catch (const std::exception &e)
            {
                emit errorOccurred(QString("Error deleting task assignemnt: %1").arg(e.what()));
            }
            return result;
        }

        bool MainController::assignmentTaskUser(const int &taskId, const QList<int> idUsers)
        {
            bool result = false;
            try
            {
                TaskPtr taskToUPdate = getTaskById(taskId);
                if(taskToUPdate){
                    result = m_taskManager->assignmentUser(taskId, idUsers);
                    if(result){
                        // emit m_taskManager->taskUpdated(taskToUPdate);
                        return result;
                    }
                }
            }
            catch (const std::exception &e)
            {
                emit errorOccurred(QString("Error adding task assignemnt: %1").arg(e.what()));
            }
            return result;
        }

        QList<QObject *> MainController::getUsersAsQObjects()
        {
            QList<QObject *> userObjects;
            QList<UserPtr> users = getAllUsers();
            for (UserPtr user : users)
            {
                if (user)
                {
                    QObject *obj = dynamic_cast<QObject *>(user);
                    if (obj)
                    {
                        userObjects.append(obj);
                    }
                    else
                    {
                        qDebug() << "User is not a QObject!";
                    }
                }
                else
                {
                    qDebug() << "Encountered null User!";
                }
            }
            return userObjects;
        }

        void MainController::updateUserRole(const QString &userID, const QString &role)
        {
            try
            {
                int id = userID.toInt();
                qDebug() << "ID USER : " << id;
                m_userManager->updateUserRole(id, role);
                emit userRoleUpdated(id, role);
            }
            catch (const std::exception &e)
            {
                qDebug() << "Exception occurred in updateUserRole: " << e.what();
                emit errorOccurred(QString("Failed to update user role: %1").arg(e.what()));
            }
        }

        SecurityManager *MainController::securityManager()
        {
            return m_securityManager.get();
        }

        void MainController::executeTask(int taskId){
            m_taskManager->executionTask(taskId);
            generateReport();
            m_statistic = m_taskManager->calculateStatistics();
            emit tasksChanged();
        }

        void MainController::generateReport(){
            // qDebug()  << "Tonga eto";
            m_report = m_taskManager->generateReport(1);
            emit reportChanged();
        }

        /**
         * @brief MainController::readNotification
         * Mark a specific notification as read -> Change the status to 0
         * @param notificationId
         */
        void MainController::readNotification(int notificationId)
        {
            NotificationManager::getInstance(m_dbManager, this).readNotification(notificationId);
        }

        ProductivityReport* MainController::report() const {
            return m_report.get();
        }

        // void MainController::syncTasks()
        // {
        //     if (m_networkManager->isConnected()) {
        //         // Logique pour synchroniser les tâches avec un serveur distant
        //         // Après la synchronisation :
        //         emit tasksChanged();
        //     } else {
        //         emit errorOccurred("Cannot sync tasks: No network connection");
        //     }
        // }

        // Test function in the SecurityManager
        // void MainController::testSecurityFunctions() {
        //     auto aesStrategy = std::make_unique<AESEncryptionStrategy>();
        //     m_securityManager->setEncryptionStrategy(std::move(aesStrategy));
        //     QString password = "myPassword";
        //     QString hashedPassword = m_securityManager->hashPassword(password);
        //     qDebug() << "Hashed password:" << hashedPassword;

        //     bool authSuccess = m_securityManager->authenticate("example_user", password);
        //     qDebug() << "Authentication success:" << authSuccess;

        //     bool passwordVerified = m_securityManager->verifyPassword(password, hashedPassword);
        //     qDebug() << "Password verified:" << passwordVerified;

        //     QByteArray data = "e";
        //     QByteArray encryptedData = m_securityManager->encryptData(data);
        //     qDebug() << "Encrypted data:" << encryptedData;

        //     QByteArray decryptedData = m_securityManager->decryptData(encryptedData);
        //     qDebug() << "Decrypted data:" << decryptedData;

        //     m_securityManager->logSecurityEvent("Test event");
        // }

        bool MainController::hasPrevious() const
        {
            return m_taskIterator && m_taskIterator->hasPrevious();
        }
        bool MainController::hasNext() const
        {
            return m_taskIterator && m_taskIterator->hasNext();
        }

        void MainController::nextPage(){
            if (m_taskIterator->hasNext()) {
                auto tasks = m_taskIterator->next();
                emitTasksChanged(tasks);
            }
        }

        void MainController::previousPage(){
            if (m_taskIterator->hasPrevious()) {
                auto tasks = m_taskIterator->previous();
                emitTasksChanged(tasks);
            }
        }

        void MainController::applyFilter(const QString& searchText){
            m_taskIterator->setFilter([searchText](const TaskPtr& task){
                return task->getTitle().contains(searchText);
            });
            m_taskIterator->apply();
            auto tasks=m_taskIterator->next();
            emitTasksChanged(tasks);
        }

        void MainController::applySort(int sortType){
            m_taskIterator->setSort([sortType](const TaskPtr &a,const TaskPtr& b){
                if(sortType==1){
                    return a->getCreatedAt() > b->getCreatedAt();
                }else if(sortType==2){
                    return a->getCreatedAt() < b->getCreatedAt();
                }
                return false;
            });
            m_taskIterator->apply();
            auto tasks=m_taskIterator->next();
            emitTasksChanged(tasks);
        }

        void MainController::emitTasksChanged(const QList<TaskPtr>& tasks){
            qDeleteAll(m_tasks);
            m_tasks.clear();
            for (const TaskPtr &task : tasks) {
                Task *tache = new Task();
                tache->setId(task->getId());
                tache->setTitle(task->getTitle());
                tache->setCreatedAt(task->getDueDate());
                tache->setPriority(task->getPriority());
                tache->setCreatedAt(task->getCreatedAt());
                tache->setStatus(task->getStatus());
                tache->setDescription(task->getDescription());
                tache->setDueDate(task->getDueDate());
                tache->setType(task->getType());
                m_tasks.append(tache);
            }
            emit tasksChanged();
            qDebug() << "Tasks updated and signal emitted.";
        }

        void MainController::doSync()
        {
            try
            {
                m_synchManager->startSync();
            }
            catch(const ExceptionManager &e)
            {
                emit m_synchManager->synchCompleted(e.message());
            }
        }
        void MainController::updateRetentionConfig(const QString& mois, const QString& jour, const QString& heure, const QString& minute) {
            if (mois.isEmpty() || jour.isEmpty() || heure.isEmpty() || minute.isEmpty()) {
                emit m_synchManager->retentionConfigCompleted("Failed", "All parameters must be non-empty.");
                return;
            }
            bool moisOk, jourOk, heureOk, minuteOk;
            int moiss = mois.toInt(&moisOk);
            int jourr = jour.toInt(&jourOk);
            int heuree = heure.toInt(&heureOk);
            int minutee = minute.toInt(&minuteOk);

            if (!moisOk || !jourOk || !heureOk || !minuteOk) {
                emit m_synchManager->retentionConfigCompleted("Failed", "All parameters must be numeric.");
                return;
            }
            try
            {
                m_synchManager->retentionBackup(moiss, jourr, heuree, minutee);
            }
            catch(const ExceptionManager &e)
            {
                emit m_synchManager->retentionConfigCompleted("Failed", e.message());
            }
            
           
        }
        /**
         * @brief MainController::countNotification
         * It will take the number of notification that hasn't been read
         * @return
         */
        int MainController::countNotification()
        {
            int count = NotificationManager::getInstance(m_dbManager, this).countUnreadNotification();
            return count;
        }
        SubscriptionManager *MainController::subscriptionManager() const
        {
            return m_subscriptionManager.get();
        }


        StatisticsModel* MainController::statisticmodel() const {
            return m_statistic.get();
        }

        /**
         * @brief MainController::unreadNotification
         * Get list of unread notification of the active user
         * @return
         */
        QList<Notification *> MainController::unreadNotification()
        {
            return NotificationManager::getInstance(m_dbManager, this).getUnreadNotifications();
        }

}


