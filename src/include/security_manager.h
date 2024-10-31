#ifndef SECURITY_MANAGER_H
#define SECURITY_MANAGER_H

#include <QObject>
#include <QByteArray>
#include <memory>
#include "../include/encryption_strategy.h"
#include <QDebug>
#include "../include/database_manager.h"
#include <QSettings>

class SecurityManager : public QObject{
    Q_OBJECT
    public :
        explicit SecurityManager(QObject *paret=nullptr);

        void setEncryptionStrategy(std::unique_ptr<EncryptionStrategy> strategy);
        QByteArray encryptData(const QByteArray& data);
        QByteArray decryptData(const QByteArray& encryptedData);
        QString hashPassword(const QString& password);
        QString decryptPassword(const QString& encryptedBase64Password);
        bool authenticate(const QString& username,const QString& password);
        void logout();
        bool isLoggedIn() const;
        bool verifyPassword(const QString& password, const QString& hashedPassword);

        void logSecurityEvent(const QString& event);
    signals:
        void securityEvent(const QString& event);
        void userConnected();

    private:
        std::unique_ptr<EncryptionStrategy> m_encryptionStrategy;
        bool m_isLoggedIn;
        DatabaseManager* m_db;
};

#endif
