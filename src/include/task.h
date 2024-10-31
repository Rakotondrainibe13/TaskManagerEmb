#pragma once

#include <QString>
#include <QDateTime>
#include <QList>
#include <memory>
#include <QObject>
#include <QThreadPool>
#include <QSqlDatabase>
#include "user.h"

class Task;
using TaskPtr = std::shared_ptr<Task>;

class Task : public QObject , public std::enable_shared_from_this<Task>, public QRunnable{
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle WRITE setTitle CONSTANT)
    Q_PROPERTY(QDateTime dateTask READ getCreatedAt CONSTANT)
    Q_PROPERTY(QDateTime duedate READ getDueDate CONSTANT)
    Q_PROPERTY(Status status READ getStatus CONSTANT)
    Q_PROPERTY(Priority priotity READ getPriority CONSTANT)
    Q_PROPERTY(int taskId READ getId CONSTANT)
    Q_PROPERTY(QString taskType READ getType CONSTANT)
    Q_PROPERTY(QString description READ getDescription CONSTANT)
    Q_PROPERTY(QString priorityString READ priorityString CONSTANT)

public:
    enum class Priority { Low=1, Medium=2, High=3 };
    enum class Status { NotStarted, InProgress, Completed };

    void run() override;

    explicit Task(QObject *parent = nullptr);
    Task(const QString& title, Priority priority = Priority::Medium);

    int getId() const;
    void setId(const int& id);

    QString getTitle() const;
    void setTitle(const QString& title);

    virtual QString getType() const;
    void setType(const QString& type);

    QString getDescription() const;
    void setDescription(const QString& description);

    Priority getPriority() const;
    void setPriority(Priority priority);

    QString priorityString();
    QString statusString();

    Status getStatus() const;
    void setStatus(Status status);

    QDateTime getDueDate() const;
    void setDueDate(const QDateTime& dueDate);

    QDateTime getStartDateEstim() const;
    void setStartDateEstim(const QDateTime& startDateEstim);

    QDateTime getStartDateReal() const;
    void setStartDateReal(const QDateTime& startDateReal);

    QDateTime getCreatedAt() const;
    void setCreatedAt(const QDateTime& createdAt);
    QDateTime getUpdatedAt() const;

    QList<TaskPtr> getDependenciesTasks() const;
    void setDependenciesTasks(const QList<TaskPtr>& dependenciesTasks);

    // Méthodes pour gérer les dépendances
    void addDependency(int taskId);
    void removeDependency(int taskId);
    QList<int> getDependencies() const;
    bool hasDependencies() const;
    bool isDependentOn(int taskId) const;




private:
    int m_id;
    QString m_title;
    QString m_description;
    QString m_type;
    Priority m_priority;
    Status m_status;
    QDateTime m_dueDate;
    QDateTime m_startDateEstim;
    QDateTime m_startDateReal;
    QDateTime m_createdAt;
    QDateTime m_updatedAt;
    QList<int> m_dependenciesIds;
    QList<TaskPtr> m_dependenciesTasks;
};
