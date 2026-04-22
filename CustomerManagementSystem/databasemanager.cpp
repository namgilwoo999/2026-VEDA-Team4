#include "databasemanager.h"
#include <QDir>

DatabaseManager::DatabaseManager() {}

void DatabaseManager::Init()
{
    QDir().mkpath("data");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","main_connection");
    db.setDatabaseName("data/mydatabase.db");
    if (!db.open()) {
        qDebug() << "DB Open Error:" << db.lastError().text();
        return;
    }

    CreateTables();
}

void DatabaseManager::CreateTables()
{
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL, "
        "password TEXT NOT NULL, "
        "name TEXT, "
        "birthdate DATE, "
        "phone TEXT, "
        "email TEXT, "
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ")"
        );

    query.exec(
        "CREATE TABLE IF NOT EXISTS items ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "category TEXT, "
        "price INTEGER, "
        "image_path TEXT, "
        "quantity INTEGER"
        ")"
        );

    query.exec(
        "CREATE TABLE IF NOT EXISTS orders ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "user_id INTEGER NOT NULL, "
        "item_id INTEGER NOT NULL, "
        "quantity INTEGER, "
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
        "FOREIGN KEY(user_id) REFERENCES users(id), "
        "FOREIGN KEY(item_id) REFERENCES items(id)"
        ")"
        );
}