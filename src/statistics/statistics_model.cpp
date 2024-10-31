#include "statistics_model.h"
#include <QDebug>

StatisticsModel::StatisticsModel(QObject *parent)
    : QObject(parent), m_todoValue(0.0), m_inProgressValue(0.0), m_completedValue(0.0), m_delayedValue(0.0) {
    updateStatistics();
    fetchDelayedTasks();
    fetchTaskActivityByDay();
}

double StatisticsModel::todoValue() const { return m_todoValue; }
double StatisticsModel::inProgressValue() const { return m_inProgressValue; }
double StatisticsModel::completedValue() const { return m_completedValue; }
double StatisticsModel::delayedValue() const { return m_delayedValue; }

void StatisticsModel::refreshStatistics() {
    updateStatistics();
}

// Setters
void StatisticsModel::setTodoValue(double value) {
    if (m_todoValue != value) {
        m_todoValue = value;
        emit todoValueChanged();
    }
}

void StatisticsModel::setInProgressValue(double value) {
    if (m_inProgressValue != value) {
        m_inProgressValue = value;
        emit inProgressValueChanged();
    }
}

void StatisticsModel::setCompletedValue(double value) {
    if (m_completedValue != value) {
        m_completedValue = value;
        emit completedValueChanged();
    }
}

void StatisticsModel::setDelayedValue(double value) {
    if (m_delayedValue != value) {
        m_delayedValue = value;
        emit delayedValueChanged();
    }
}

QList<int> StatisticsModel::taskActivity() const {
    return m_taskActivity;
}


QList<QString> StatisticsModel::delayedTasks() const {
    return m_delayedTasks;
}

void StatisticsModel::fetchDelayedTasks() {
    m_delayedTasks.clear();
    QSqlQuery query;
    query.exec("SELECT title, julianday('now') - julianday(due_date) AS delaye FROM tasks WHERE due_date < datetime('now') and status < 2");

    while (query.next()) {
        QString title = query.value(0).toString();
        int delay = query.value(1).toInt();
        m_delayedTasks.append(QString("%1 - %2 jours de retard").arg(title).arg(delay));
    }

    emit delayedTasksChanged();
}

void StatisticsModel::updateStatistics() {
    // Example query; replace with your actual SQL queries
    QSqlQuery query;

    query.exec("SELECT COUNT(*) FROM tasks WHERE status = 0");
    if (query.next()) {
        m_todoValue = query.value(0).toDouble();
        qDebug() << m_todoValue << "todovalue";
    }
    query.exec("SELECT COUNT(*) FROM tasks WHERE status = 1");
    if (query.next()) {
        m_inProgressValue = query.value(0).toDouble();
    }

    query.exec("SELECT COUNT(*) FROM tasks WHERE status = 2");
    if (query.next()) {
        m_completedValue = query.value(0).toDouble();
    }

    query.exec("SELECT COUNT(*) FROM tasks WHERE due_date < datetime('now') and status < 2");
    if (query.next()) {
        m_delayedValue = query.value(0).toDouble();  // Assuming you want to track the count of overdue tasks
        qDebug() << m_delayedValue << "overdue tasks";
    }

    emit todoValueChanged();
    emit inProgressValueChanged();
    emit completedValueChanged();
    emit delayedValueChanged();
}
