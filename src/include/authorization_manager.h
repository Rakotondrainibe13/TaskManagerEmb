#ifndef AUTHORIZATIONMANAGER_H
#define AUTHORIZATIONMANAGER_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QStringList>

class AuthorizationManager : public QObject {
    Q_OBJECT
public:
    explicit AuthorizationManager(QObject *parent = nullptr);

    Q_INVOKABLE bool hasAccess(const QString &resource);

private:
    QHash<QString, QStringList> m_rolePermissions;
};

#endif
