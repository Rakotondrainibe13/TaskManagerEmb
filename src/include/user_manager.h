#pragma once

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>

#include "../include/user.h"
#include "../include/database_manager.h"

class UserManager : public QObject {
    Q_OBJECT
public:
    explicit UserManager(QObject *parent = nullptr);
    explicit UserManager(std::shared_ptr<DatabaseManager> databaseManager, QObject *parent = nullptr);

    // Méthodes de gestion des Users
    void updateUserRole(int& id, const QString& role);
    QList<UserPtr> getAllUsers() const;

    void logUserEvent(const QString& event);

signals:
    void userEvent(const QString& event);

private:
    std::shared_ptr<DatabaseManager> m_dbManager;
};



