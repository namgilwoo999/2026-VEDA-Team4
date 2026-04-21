#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

class DatabaseManager
{
public:
    DatabaseManager();
    static void Init();
private:
    static void CreateTables();
};

#endif // DATABASEMANAGER_H
