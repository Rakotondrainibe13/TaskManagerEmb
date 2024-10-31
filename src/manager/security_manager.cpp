#include "../include/security_manager.h"
#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QSqlError>
#include <QSettings>

SecurityManager::SecurityManager(QObject *parent)
    : QObject(parent), m_isLoggedIn(false) {}

void SecurityManager::setEncryptionStrategy(std::unique_ptr<EncryptionStrategy> strategy){
    m_encryptionStrategy = std ::move(strategy);
}

QByteArray SecurityManager::encryptData(const QByteArray& data){
    if(m_encryptionStrategy){
        return m_encryptionStrategy->encrypt(data);
    }
    return QByteArray();
}

QByteArray SecurityManager::decryptData(const QByteArray& encryptedData){
    if(m_encryptionStrategy){
        return m_encryptionStrategy->decrypt(encryptedData);
    }
    return QByteArray();
}

QString SecurityManager::hashPassword(const QString& password) {
    QByteArray byteArrayPassword = password.toUtf8();
    QByteArray encryptedPassword = encryptData(byteArrayPassword);
    return QString::fromUtf8(encryptedPassword.toBase64());
}

QString SecurityManager::decryptPassword(const QString& encryptedBase64Password) {
    QByteArray encryptedPassword = QByteArray::fromBase64(encryptedBase64Password.toUtf8());
    QByteArray decryptedPassword = decryptData(encryptedPassword);
    return QString::fromUtf8(decryptedPassword);
}

bool SecurityManager::verifyPassword(const QString& password, const QString& hashedPassword) {
    QByteArray byteArrayPassword = password.toUtf8();
    QByteArray hashedPasswordBytes = QByteArray::fromBase64(hashedPassword.toUtf8());
    QByteArray encryptedPassword = encryptData(byteArrayPassword);
    return encryptedPassword == hashedPasswordBytes;
}

void SecurityManager::logout(){
    QSettings settings("TaskEmb", "TaskEmb");
    settings.clear();
    m_isLoggedIn = false;
    logSecurityEvent("User logged out!");
}

bool SecurityManager::authenticate(const QString& email, const QString& password) {
    QSettings settings("TaskEmb", "TaskEmb");
    settings.clear();
    std::shared_ptr<DatabaseManager> dbManager = DatabaseManager::instance();
    QString hashedPassword = hashPassword(password);
    qDebug() << hashedPassword;
    QSqlQuery query(*dbManager->getDatabase());
    query.prepare("SELECT id, username, email, roleuser, password_hash FROM users WHERE email = :email");
    query.bindValue(":email", email);
    if (!query.exec()) {
        logSecurityEvent("Database query error: " + query.lastError().text());
        return false;
    }
    if (query.next()) {
        QString storedHash = query.value("password_hash").toString();
        qDebug() << storedHash;
        if (verifyPassword(password, storedHash)) {
            m_isLoggedIn = true;
            int userId = query.value("id").toInt();
            QString roleUser = query.value("roleuser").toString();
            QString pseudo = query.value("username").toString();
            settings.setValue("userID", userId);
            settings.setValue("username", pseudo);
            settings.setValue("roleUser", roleUser);
            settings.setValue("email", email);
            logSecurityEvent("User authenticated successfully!");
            emit userConnected();
            return true;
        }
    }
    logSecurityEvent("Authentication failed!");
    return false;
}

bool SecurityManager::isLoggedIn() const {
    return m_isLoggedIn;
}

void SecurityManager::logSecurityEvent(const QString& event) {
    emit securityEvent(event);
    qDebug() << "Security Event:" << event;
}
