#include "databasemanager.h"
#include <QDir>

DatabaseManager::DatabaseManager() {
}
void DatabaseManager::Init() {
    QDir().mkpath("data");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data/mydatabase.db");

    if (!db.open()) {
        // 에러 처리
        return;
    }

    CreateTables();
}
void DatabaseManager::CreateTables() {
    QSqlQuery query;

    // users
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

    // items
    query.exec(
        "CREATE TABLE IF NOT EXISTS items ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "category TEXT, "
        "price INTEGER, "
        "image_path TEXT"
        ")"
        );

    // orders
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