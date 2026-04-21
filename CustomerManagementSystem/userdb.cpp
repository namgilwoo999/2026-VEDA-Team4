#include "userdb.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool UserDB::UsernameExists(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM users WHERE username = :username");
    query.bindValue(":username", username);
    return query.exec() && query.next();
}

bool UserDB::AddUser(const User &user)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO users (username, password, name, birthdate, phone, email) "
        "VALUES (:username, :password, :name, :birthdate, :phone, :email)"
    );
    query.bindValue(":username", user.GetId());
    query.bindValue(":password", user.GetPassword());
    query.bindValue(":name",     user.GetName());
    query.bindValue(":birthdate", user.GetBirth().toString(Qt::ISODate));
    query.bindValue(":phone",    user.GetPhone());
    query.bindValue(":email",    user.GetEmail());

    if (!query.exec()) {
        qWarning() << "AddUser failed:" << query.lastError().text();
        return false;
    }
    return true;
}
