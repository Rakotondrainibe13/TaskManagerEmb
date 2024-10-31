#include <QDebug>
#include "../include/task_manager.h"
#include "../include/task_mapper.h"
#include "../include/projet_task_mapper.h"
#include "../profiler/profiler.h"

#define PROFILE_FUNCTION Profiler::Profiler __profiler(__FUNCTION__);

#include "report/productivityReport.h"
#include <QDebug>
#include <QString>
#include "statistics/statistics_model.h"
#include "include/database_manager.h"
#include <QTimer>

TaskManager::TaskManager(QObject *parent): QObject(parent){}

TaskManager::TaskManager(std::shared_ptr<TaskFactory> taskFactory,std::shared_ptr<DatabaseManager> databaseManager, QObject *parent)
    : QObject(parent),
    m_taskFactory(taskFactory),
    m_dbManager(databaseManager)
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TaskManager::onOverdueTasks);
    // timer->start(60000);  // One hour
    timer->start(3600000);  // One hour
}


bool TaskManager::updateTask(TaskPtr task){
    PROFILE_FUNCTION;
    try {
        TaskPtr updatedTask = getTask(task->getId());
        if (updatedTask) {
            updatedTask->setTitle(task->getTitle());
            updatedTask->setDescription(task->getDescription());
            updatedTask->setPriority(static_cast<Task::Priority>(task->getPriority()));
            // updatedTask->setStatus(static_cast<Task::Status>(task->getStatus()));
            updatedTask->setDueDate(task->getDueDate());

            bool result = m_dbManager->updateTask(updatedTask);
            if(!result) qDebug() << (QString("The task %1 has not been updated").arg(updatedTask->getId()));

            for(const auto &observer : m_observers){
                observer->onTaskEvent(updatedTask, TaskObserver::TaskEvent::Updated);
            }
            const int idtask = updatedTask->getId();
            emit updatedTaskSignal(idtask);

            return result;
        }
    } catch (const std::exception& e) {
        throw e.what();
    }
    return false;
}

void TaskManager::updateStatus(TaskPtr& task){
    PROFILE_FUNCTION;
    try{
        bool result = m_dbManager->updateTask(task);
        if(!result) qDebug() << (QString("The task %1 has not been updated").arg(task->getId()));
    } catch (const std::exception& e) {
        throw e.what();
    }
}

void TaskManager::removeTask(int taskId)
{
    PROFILE_FUNCTION;
    try {
        TaskPtr ptrTask=getTask(taskId);
        for(const auto &observer : m_observers){
            observer->onTaskEvent(ptrTask, TaskObserver::TaskEvent::Deleted);
        }
        bool result = m_dbManager->deleteTask(taskId);
        if(!result) qDebug() << "The task has not been removed";
    } catch (const std::exception& e) {
        throw e.what();
    }
}

TaskPtr TaskManager::getTask(int taskId) const{
    PROFILE_FUNCTION;
    QList<TaskPtr> tasks;
    TaskMapper taskMapper(tasks,m_taskFactory);
    QString query=QString("SELECT * FROM Tasks where id=%1;").arg(taskId);
    m_dbManager->executeSelectQuery(query, taskMapper);

    return tasks.first();
}

QList<TaskPtr> TaskManager::getAllTasks() const{
    PROFILE_FUNCTION
    QList<TaskPtr> tasks;
    TaskMapper taskMapper(tasks,m_taskFactory);
    m_dbManager->executeSelectQuery("SELECT * FROM Tasks;", taskMapper);
    return tasks;
}

QList<TaskPtr> TaskManager::getAllTasksByIdUser(int userId) const{
    QList<TaskPtr> tasks;
    TaskMapper taskMapper(tasks,m_taskFactory);
    const QString queryStr = QString::fromLatin1("SELECT * FROM Tasks where id in(select task_id from TaskAssignments where user_id="+std::to_string(userId)+");");
    m_dbManager->executeSelectQuery(queryStr, taskMapper);
    return tasks;
}

QList<TaskPtr> TaskManager::getAllTasksAtAGivenDate(const QDate& date) const{
    QList<TaskPtr> tasks;
    TaskMapper taskMapper(tasks,m_taskFactory);
    const QString queryStr = QString::fromLatin1("SELECT * FROM Tasks where '%1' >= strftime('%Y-%m-%d',due_Date) and '%1'<= strftime('%Y-%m-%d',due_Date) ;").arg(date.toString("yyyy-MM-dd"));
    m_dbManager->executeSelectQuery(queryStr, taskMapper);
    return tasks;
}

std::unique_ptr<TaskIterator> TaskManager::createIterator(int& pageSize) const {
    QList<TaskPtr> tasks = getAllTasks();
    return std::make_unique<TaskIterator>(tasks, pageSize);
}


/**
 * @brief TaskManager::getAllOverdueTasks
 * Get all tasks overdued in order to notify all observers -> All usres concerned
 * @return
 */
QList<TaskPtr> TaskManager::getAllOverdueTasks() const
{
    QList<TaskPtr> tasks;
    TaskMapper taskMapper(tasks,m_taskFactory);
    const QString queryStr = "SELECT * FROM tasks WHERE due_date IS NOT NULL AND due_date < datetime('now')";
    m_dbManager->executeSelectQuery(queryStr, taskMapper);
    return tasks;
}

/**
 * @brief TaskManager::onOverdueTasks
 * Check for all overdue tasks
 */
void TaskManager::onOverdueTasks()
{
    QList<TaskPtr> overdueTasks(getAllOverdueTasks());

    for(const auto &task : overdueTasks){
        for(const auto &observer : m_observers){
            observer->onTaskEvent(task, TaskObserver::TaskEvent::Overdue);
        }
    }
}

std::shared_ptr<SubscriptionManager> TaskManager::subscriptionManager() const
{
    return m_subscriptionManager;
}

void TaskManager::setSubscriptionManager(const std::shared_ptr<SubscriptionManager> &newSubscriptionManager)
{
    m_subscriptionManager = newSubscriptionManager;
}


void TaskManager::addSubtask(int parentTaskId, TaskPtr subtask){
    PROFILE_FUNCTION;
    try{
        std::shared_ptr<ProjectTask> parentTask= std::dynamic_pointer_cast<ProjectTask>(getTask(parentTaskId));
        if(parentTask){
            if(!m_dbManager->addSubtask(parentTaskId,subtask->getId())){
                throw std::runtime_error("Error adding subtask");
            }
            parentTask->addSubtask(subtask);
        }
    }catch(const std::exception& e){
        throw &e;
    }
}

void TaskManager::removeSubtask(int parentTaskId, int subtaskId){
    PROFILE_FUNCTION;
    try{
        std::shared_ptr<ProjectTask> parentTask= std::dynamic_pointer_cast<ProjectTask>(getTask(parentTaskId));
        TaskPtr subtask= getTask(subtaskId);
        if(parentTask && subtask){
            if(!m_dbManager->removeSubtask(parentTaskId,subtaskId)){
                throw std::runtime_error("Error removing subtask");
            }
            parentTask->removeSubtask(subtask);
        }
    }
    catch(const std::exception& e){
        throw &e;
    }
}

/**
 * @brief TaskManager::registerObserver Adding observer for the taskManager
 * @param observer
 */
void TaskManager::registerObserver(TaskObserver *observer)
{
    m_observers.append(observer);
}

TaskPtr TaskManager::createTask(const QString& title, const QString& description, int priority, const QDateTime& dueDate, int type){
    PROFILE_FUNCTION
    Task::Priority taskPriority = static_cast<Task::Priority>(priority);
    TaskFactory::TaskType taskType = static_cast<TaskFactory::TaskType>(type);

    try {
        if (countTasks() >= MAX_FREE_TASK_NUMBER && m_subscriptionManager->currentSubscription() == nullptr) {
            throw max_task_exception();
        }

        TaskPtr newTask = m_taskFactory->createTask(taskType, title);

        if (newTask) {
            newTask->setDescription(description);
            newTask->setPriority(taskPriority);
            newTask->setDueDate(dueDate);

            int taskId = m_dbManager->saveTaskGetId(newTask);
            newTask->setId(taskId);
        }
        generateReport(1);
        for(const auto &observer : m_observers){
            observer->onTaskEvent(newTask, TaskObserver::TaskEvent::Created);
        }
        return newTask;
    } catch (const max_task_exception& e) {
        QString errorMessage(e.what());
        emit maxTaskNumberReached(errorMessage);
    }

    return nullptr;
}

void TaskManager::executeTask(Task* task){
    m_executionStrategy->execute(task);
}

void TaskManager::setExecutionStrategy(std::shared_ptr<TaskExecution::ITaskExecutionStrategy> strategy){
    m_executionStrategy=strategy;
}

void TaskManager::populateSubtask(ProjectTask* projetTask){
    ProjetTaskMapper taskMapper(projetTask);
    const QString query=QString("SELECT * FROM TaskImbrication where task_id='%1';").arg(projetTask->getId());
    m_dbManager->executeSelectQuery(query, taskMapper);
}

void TaskManager::taskExecutionStrategy(Task* task){
    PROFILE_FUNCTION;
    if (ProjectTask* projectTask= dynamic_cast<ProjectTask*>(task)){
        populateSubtask(projectTask);
        QList<TaskPtr> subTasks=projectTask->getSubtasksObj();
        for(TaskPtr subTask:subTasks){
            if(subTask->getDependencies().size()>0){
                std::shared_ptr<TaskExecution::SequentialExecutionStrategy> simple=std::make_shared<TaskExecution::SequentialExecutionStrategy>();
                setExecutionStrategy(simple);
                return;
            }
        }
        std::shared_ptr<TaskExecution::ParallelExecutionStrategy> simple=std::make_shared<TaskExecution::ParallelExecutionStrategy>();
        setExecutionStrategy(simple);
        return;
    }
    std::shared_ptr<TaskExecution::SimpleExecutionStrategy> simple=std::make_shared<TaskExecution::SimpleExecutionStrategy>();
    setExecutionStrategy(simple);
    return;
}

void TaskManager::executionTask(int taskId){
    TaskPtr ptrTask=getTask(taskId);
    Task* task=ptrTask.get();
    taskExecutionStrategy(task);
    executeTask(task);
    updateStatus(ptrTask);
    for(const auto &observer : m_observers){
        observer->onTaskEvent(ptrTask, TaskObserver::TaskEvent::StatusChanged);
    }
}

std::unique_ptr<ProductivityReport> TaskManager::generateReport(int user_id){
    // QList<TaskPtr> tasks = getAllTasksByIdUser(user_id);
    QList<TaskPtr> tasks = getAllTasks();
    qDebug() << "Task via db" << tasks.size();
    std::unique_ptr<ProductivityReport> report = std::make_unique<ProductivityReport>(tasks);
    report->generateReport();
    return report;
}



/**
 * @brief TaskManager::usersAssigned
 * Get the list of users assigned to a task
 * @param task
 * @return
 */
QList<UserPtr> TaskManager::usersAssigned(int taskId)
{
    return m_dbManager->usersAssigned(taskId, this);
}

QList<User *> TaskManager::usersNotAssigned(int taskId)
{
    return m_dbManager->usersNotAssigned(taskId, this);
}

bool TaskManager::unassignmentUser(int taskId, int userId)
{
    try {
        bool result = m_dbManager->deleteUserAssigned(userId, taskId);
        if(!result) qDebug() << "The task assignment is not deleted";
        emit userAssignmentChanged();
        return result;
    } catch (const std::exception& e) {
        throw e.what();
    }
    return false;
}

bool TaskManager::assignmentUser(int taskId, const QList<int>& idUsers)
{
    QSqlDatabase *connection = nullptr;
    try {
        connection = m_dbManager->getDatabase().get();
        if(connection && connection -> transaction()){
            QSqlQuery query(*connection);
            for(auto const &i : idUsers){
                auto temp = m_dbManager->addUserAssigned(taskId, i, &query);
                if(temp == false){
                    connection->rollback();
                    return false;
                }
            }

            if(!connection->commit()){
                qDebug() << "Failed to commit";
            }

            // NO rollback here, so notify all users
            TaskPtr ptrTask=getTask(taskId);
            for(auto const &i : idUsers){
                for(const auto &observer : m_observers){
                    observer->onTaskAssigned(ptrTask, i);
                }
            }
            emit userAssignmentChanged();
            qDebug() << "Users assigned";
            return true;
        }
        return false;
    } catch (const std::exception& e) {
        throw e.what();
    }
}

int TaskManager::countTasks()
{
    try {
        QSqlQuery query(*m_dbManager->getDatabase());

        query.prepare(R"(
            SELECT COUNT(*) as task_number FROM Tasks;
        )");


        if (!query.exec()) {
            qDebug() << "Query execution failed : " << query.lastError().text();
        }

        if (query.next()) {
            return query.value("task_number").toInt();
        }

        return 0;
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
}

std::unique_ptr<StatisticsModel> TaskManager::calculateStatistics(){
    std::shared_ptr<QSqlDatabase> database = m_dbManager->getDatabase();
    std::unique_ptr<StatisticsModel> statistic = std::make_unique<StatisticsModel>();
    try {

        QSqlQuery query(*database);
        query.prepare(R"(
            SELECT COUNT(*) as statistic,status FROM tasks group by status order by status asc
        )");
        if (!query.exec()) {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
        while (query.next()) {
            // qDebug()<<"STATUS"<<query.value("status").toInt();
            if(query.value("status").toInt() == 0){
                statistic->setTodoValue(query.value("statistic").toDouble());
            }else if(query.value("status").toInt() == 1){
                statistic->setInProgressValue(query.value("statistic").toDouble());
            }else{
                statistic->setCompletedValue(query.value("statistic").toDouble());
            }
        }
        qDebug() << "STATISTIQUE =" <<  statistic->completedValue();
    } catch (const std::exception& e) {
        qDebug()<< "???";
        qWarning() << "An unknown exception occurred on getting all uisers that NOT assigned to a taskid ";
    }
     return statistic;


}

