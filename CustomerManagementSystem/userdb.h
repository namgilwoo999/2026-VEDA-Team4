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
};

#endif // USERDB_H
