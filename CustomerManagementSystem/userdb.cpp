#include "userdb.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool UserDB::UsernameExists(const QString &username) {
    // 해당 아이디 행이 하나라도 존재하면 true 반환
    QSqlQuery query(QSqlDatabase::database("main_connection"));
    query.prepare("SELECT 1 FROM users WHERE username = :username");
    query.bindValue(":username", username);
    return query.exec() && query.next();
}

bool UserDB::VerifyPassword(const QString &username, const QString &password) {
    // 아이디와 비밀번호가 모두 일치하는 행이 존재하면 true 반환
    QSqlQuery query(QSqlDatabase::database("main_connection"));
    query.prepare("SELECT 1 FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    return query.exec() && query.next();
}

bool UserDB::UpdatePassword(const QString &username, const QString &newPassword) {
    QSqlQuery query(QSqlDatabase::database("main_connection"));
    query.prepare("UPDATE users SET password = :password WHERE username = :username");
    query.bindValue(":password", newPassword);
    query.bindValue(":username", username);
    if (!query.exec()) {
        qWarning() << "UpdatePassword failed:" << query.lastError().text();
        return false;
    }
    return true;
}

bool UserDB::DeleteUser(const QString &username) {
    QSqlQuery query(QSqlDatabase::database("main_connection"));
    query.prepare("DELETE FROM users WHERE username = :username");
    query.bindValue(":username", username);
    if (!query.exec()) {
        qWarning() << "DeleteUser failed:" << query.lastError().text();
        return false;
    }
    return true;
}

bool UserDB::AddUser(const User &user) {
    QSqlQuery query(QSqlDatabase::database("main_connection"));
    query.prepare(
        "INSERT INTO users (username, password, name, birthdate, phone, email) "
        "VALUES (:username, :password, :name, :birthdate, :phone, :email)"
    );
    // User 객체에서 각 필드를 바인딩
    query.bindValue(":username",  user.GetId());
    query.bindValue(":password",  user.GetPassword());
    query.bindValue(":name",      user.GetName());
    query.bindValue(":birthdate", user.GetBirth().toString(Qt::ISODate));
    query.bindValue(":phone",     user.GetPhone());
    query.bindValue(":email",     user.GetEmail());
    if (!query.exec()) {
        qWarning() << "AddUser failed:" << query.lastError().text();
        return false;
    }
    return true;
}
