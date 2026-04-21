#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

class DatabaseManager
{
public:
    DatabaseManager();
    static void Init();

private:
    static void CreateTables();
};

#endif // DATABASEMANAGER_H