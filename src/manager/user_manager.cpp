#include <QDebug>
#include <QString>

#include "../include/user_manager.h"
#include "../include/user_mapper.h"

UserManager:: UserManager(QObject *parent): QObject(parent){}
UserManager::UserManager(std::shared_ptr<DatabaseManager> databaseManager, QObject *parent)
    : QObject(parent),
    m_dbManager(databaseManager)
{}

void UserManager::logUserEvent(const QString& event){
    emit userEvent(event);
    qDebug() << "User Event:" << event;
}

void UserManager::updateUserRole(int& userID,const QString& role){
    try {
        if (userID) {
            bool result = m_dbManager->updateUserRole(userID,role);
            logUserEvent("User updated successfully!");
            if(!result) qDebug() << (QString("The User %1 has not been updated").arg(userID));
        }
    } catch (const std::exception& e) {
        logUserEvent("User has not been updated!");
        throw e.what();
    }
}

QList<UserPtr> UserManager::getAllUsers() const{
    QList<UserPtr> users;
    UserMapper userMapper(users);
    m_dbManager->executeSelectQuery("SELECT * FROM Users;",userMapper);
    qDebug() << "ATO" <<users.length() ;
    return users;
}
