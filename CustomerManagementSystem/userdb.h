#ifndef USERDB_H
#define USERDB_H

#include "user.h"
#include <QString>

class UserDB
{
public:
    UserDB() = default;

    bool AddUser(const User &user);
    bool UsernameExists(const QString &username);
    bool VerifyPassword(const QString &username, const QString &password);
    bool UpdatePassword(const QString &username, const QString &newPassword);
    bool DeleteUser(const QString &username);
};

#endif // USERDB_H
