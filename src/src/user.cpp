#include "../include/user.h"

User::User(int id, const QString &username, QObject *parent) : QObject(parent),
    m_id(id),
    m_username(username)
{}
