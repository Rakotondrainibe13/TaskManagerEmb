#include "../include/task.h"
#include <algorithm>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>  // Include for std::cout
using namespace std;

Task::Task(const QString& title, Priority priority)
    : m_title(title), 
      m_priority(priority), 
      m_status(Status::NotStarted),
      m_createdAt(QDateTime::currentDateTime()),
      m_updatedAt(QDateTime::currentDateTime()),
      QObject(nullptr)
{}

Task::Task(QObject *parent) : QObject(parent), m_priority(Priority::Medium), m_status(Status::NotStarted) {}

// void Task::update(const std::string& statistic, double value) {
//     // Handle update based on the statistic
//     if (statistic == "CompletionRate") {
//         // Do something with the completion rate
//         cout << "Task " << m_title.toStdString() << " received update: " << statistic << " = " << value << "%" << endl;
//     }
// }

int Task::getId() const{
    return m_id;
}
void Task::setId(const int& id){
    m_id=id;
}

QString Task::getTitle() const{
    return m_title;
}
void Task::setTitle(const QString& title){
    m_title = title;
}

QString Task::getType() const{
    return m_type;
}
void Task::setType(const QString& type){
    m_type = type;
}

QString Task::getDescription() const{
    return m_description;
}
void Task::setDescription(const QString& description){
    m_description = description;
}

Task::Priority Task::getPriority() const{
    return m_priority;
}
void Task::setPriority(Task::Priority priority){
    m_priority=priority;
}

Task::Status Task::getStatus() const{
    return m_status;
}
void Task::setStatus(Task::Status status){
    m_status= status;
}

QDateTime Task::getDueDate() const{
    return m_dueDate;
}
void Task::setDueDate(const QDateTime& dueDate){
    m_dueDate = dueDate;
}

QDateTime Task::getStartDateEstim() const{
    return m_startDateEstim;
}
void Task::setStartDateEstim(const QDateTime& startDateEstim){
    m_startDateEstim= startDateEstim;
}

QDateTime Task::getStartDateReal() const{
    return m_startDateReal;
}
void Task::setStartDateReal(const QDateTime& startDateReal){
    m_startDateReal= startDateReal;
}

QDateTime Task::getCreatedAt() const{
    return m_createdAt;
}
void Task::setCreatedAt(const QDateTime& createdAt){
    m_createdAt=createdAt;
}
QDateTime Task::getUpdatedAt() const{
    return m_updatedAt;
}

void Task::addDependency(int taskId) {
    if (!isDependentOn(taskId) && taskId != this->m_id) {
        m_dependenciesIds.append(taskId);
        m_updatedAt = QDateTime::currentDateTime();
    }
}

void Task::removeDependency(int taskId) {
    auto it = std::find(m_dependenciesIds.begin(), m_dependenciesIds.end(), taskId);
    if (it != m_dependenciesIds.end()) {
        m_dependenciesIds.erase(it);
        m_updatedAt = QDateTime::currentDateTime();
    }
}

QList<int> Task::getDependencies() const {
    return m_dependenciesIds;
}

bool Task::hasDependencies() const {
    return !m_dependenciesIds.isEmpty();
}

bool Task::isDependentOn(int taskId) const {
    return std::find(m_dependenciesIds.begin(), m_dependenciesIds.end(), taskId) != m_dependenciesIds.end();
}


QList<TaskPtr> Task::getDependenciesTasks() const{
    return m_dependenciesTasks;
}

void Task::setDependenciesTasks(const QList<TaskPtr>& dependenciesTasks){
    m_dependenciesTasks=dependenciesTasks;
}

QString Task::priorityString()
{
    switch (m_priority) {
        case Priority::Low:
            return "Low";
        case Priority::Medium:
            return "Medium";
        case Priority::High:
            return "High";
        default:
            return "Unknown";
    }
}

QString Task::statusString()
{
    switch (m_status) {
    case Status::NotStarted:
        return "Task Not Started";
    case Status::InProgress:
        return "Task In Progress";
    case Status::Completed:
        return "Task Completed";
    default:
        return "Unknown Status";
    }
}

void Task::run(){
    int status = static_cast<int>(m_status);
    if(status < 2)
        m_status=static_cast<Task::Status>(status+1);
}
