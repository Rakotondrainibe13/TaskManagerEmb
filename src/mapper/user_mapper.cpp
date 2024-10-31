#include "../include/user_mapper.h"
#include "../include/user.h"
#include <QSqlError>
#include <QDebug>

void UserMapper::map(QSqlQuery& query) {
    UserPtr user = new User(
        query.value("username").toString(),
        query.value("password_hash").toString(),
        query.value("email").toString()
        );
    user->setId(query.value("id").toInt());
    user->setCreatedAt(query.value("created_at").toDateTime());
    user->setRoleUser(query.value("roleuser").toString());
    results.append(user);
}



