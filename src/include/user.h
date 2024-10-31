#pragma once

#include <QString>
#include <QDateTime>
#include <memory>
#include <QObject>

class User;
using UserPtr = User*;

class User :public QObject, public std::enable_shared_from_this<User> {
    Q_OBJECT

    Q_PROPERTY(QString userID READ getIDtoString WRITE setIDtoString NOTIFY userIDChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString email READ getEmail WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString role READ getRoleUser WRITE setRoleUser NOTIFY roleUserChanged)


public:

    User(const QString& username, const QString& passwordHash, const QString& email);

    User(int id, const QString &username, QObject *parent = nullptr) ;

    Q_INVOKABLE void setRole(const QString& role);

    QString getIDtoString();
    void setIDtoString(QString& id);

    int getId() const;
    void setId(const int& id);

    QString getUsername() const;
    void setUsername(const QString& username);

    QString getPasswordHash() const;
    void setPasswordHash(const QString& passwordHash);

    QString getEmail() const;
    void setEmail(const QString& email);

    QDateTime getCreatedAt() const;
    void setCreatedAt(const QDateTime& createdAt);

    QString getRoleUser() const;
    void setRoleUser(const QString& email);

private:
    int m_id;
    QString m_username;
    QString m_passwordHash;
    QString m_email;
    QDateTime m_createdAt;
    QString m_roleuser;

signals:
    void usernameChanged();
    void emailChanged();
    void roleUserChanged();
    void userIDChanged();
};


inline void User::setRole(const QString& role) {
    m_roleuser = role;
    emit roleUserChanged();
}
inline User::User(const QString& username, const QString& passwordHash, const QString& email)
    : m_username(username), m_passwordHash(passwordHash), m_email(email), m_createdAt(QDateTime::currentDateTime()) {}

inline QString User::getIDtoString(){
    return QString::number(m_id);
}

inline void User::setIDtoString(QString& id){
    // setters
}

inline int User::getId() const {
    return m_id;
}

inline void User::setId(const int& id) {
    m_id = id;
}

inline QString User::getUsername() const {
    return m_username;
}

inline void User::setUsername(const QString& username) {
    m_username = username;
    emit usernameChanged();
}

inline QString User::getPasswordHash() const {
    return m_passwordHash;
}

inline void User::setPasswordHash(const QString& passwordHash) {
    m_passwordHash = passwordHash;
}

inline QString User::getEmail() const {
    return m_email;
}

inline void User::setEmail(const QString& email) {
    m_email = email;
    emit emailChanged();
}

inline QDateTime User::getCreatedAt() const {
    return m_createdAt;
}

inline void User::setCreatedAt(const QDateTime& createdAt) {
    m_createdAt = createdAt;
}

inline QString User::getRoleUser() const {
    return m_roleuser;
}

inline void User::setRoleUser(const QString& role) {
    m_roleuser = role;
    emit roleUserChanged();
}
