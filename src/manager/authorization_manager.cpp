#include "../include/authorization_manager.h"
#include <QSettings>
#include <QDebug>

AuthorizationManager::AuthorizationManager(QObject *parent) 
    : QObject(parent)
{
    m_rolePermissions["ADMIN"] = {"Dashboard", "NewTask", "ListTask", "Calendar","ListUser"};
    m_rolePermissions["r"] = {"Dashboard", "ListTask"};
    m_rolePermissions["rw"] = {"Dashboard", "NewTask", "ListTask", "Calendar"};
}

bool AuthorizationManager::hasAccess(const QString &resource) {
    QSettings settings("TaskEmb", "TaskEmb");
    qDebug() << "ROLE USER : " << settings.value("roleUser").toString();
    return m_rolePermissions.value(settings.value("roleUser").toString()).contains(resource);
}
