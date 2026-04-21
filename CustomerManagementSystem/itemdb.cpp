#include "itemdb.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ItemDB::ItemDB() {}

QList<Item> ItemDB::GetAllItems()
{
    QList<Item> list;

    QSqlQuery query(QSqlDatabase::database("main_connection"));

    if (!query.exec("SELECT id, name, category, price, quantity FROM items")) {
        qDebug() << "Query error:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        Item item;

        item.SetId(query.value(0).toInt());
        item.SetName(query.value(1).toString());
        item.SetCategory(query.value(2).toString());
        item.SetPrice(query.value(3).toInt());
        item.SetQuantity(query.value(4).toInt());

        list.append(item);
    }

    return list;
}

QList<Item> ItemDB::GetItemsByCategory(const QString& category)
{
    if (category == "전체")
        return GetAllItems();

    QList<Item> list;
    QSqlQuery query(QSqlDatabase::database("main_connection"));
    query.prepare(
        "SELECT id, name, category, price, quantity FROM items WHERE category=?"
        );
    query.addBindValue(category);
    if (!query.exec()) {
        qDebug() << "GetItemsByCategory error:" << query.lastError().text();
        return list;
    }
    while (query.next()) {
        Item item;
        item.SetId(query.value(0).toInt());
        item.SetName(query.value(1).toString());
        item.SetCategory(query.value(2).toString());
        item.SetPrice(query.value(3).toInt());
        item.SetQuantity(query.value(4).toInt());
        list.append(item);
    }
    return list;
}

QList<Item> ItemDB::SearchItems(const QString& keyword, const QString& category)
{
    QList<Item> list;
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    if (category == "전체") {
        query.prepare(
            "SELECT id, name, category, price, quantity FROM items "
            "WHERE name LIKE ? OR category LIKE ?"
            );
        const QString pattern = "%" + keyword + "%";
        query.addBindValue(pattern);
        query.addBindValue(pattern);
    } else {
        query.prepare(
            "SELECT id, name, category, price, quantity FROM items "
            "WHERE (name LIKE ? OR category LIKE ?) AND category = ?"
            );
        const QString pattern = "%" + keyword + "%";
        query.addBindValue(pattern);
        query.addBindValue(pattern);
        query.addBindValue(category);
    }

    if (!query.exec()) {
        qDebug() << "SearchItems error:" << query.lastError().text();
        return list;
    }
    while (query.next()) {
        Item item;
        item.SetId(query.value(0).toInt());
        item.SetName(query.value(1).toString());
        item.SetCategory(query.value(2).toString());
        item.SetPrice(query.value(3).toInt());
        item.SetQuantity(query.value(4).toInt());
        list.append(item);
    }
    return list;
}

Item ItemDB::GetItemById(int id)
{
    Item item;

    QSqlQuery query(QSqlDatabase::database("main_connection"));
    query.prepare("SELECT id, name, category, price, quantity FROM items WHERE id=?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "GetItemById error:" << query.lastError().text();
        return item;
    }

    if (query.next()) {
        item.SetId(query.value(0).toInt());
        item.SetName(query.value(1).toString());
        item.SetCategory(query.value(2).toString());
        item.SetPrice(query.value(3).toInt());
        item.SetQuantity(query.value(4).toInt());
    }

    return item;
}

bool ItemDB::InsertItem(const Item& item)
{
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    // 같은 이름 + 카테고리 있는지 먼저 확인
    query.prepare(
        "SELECT id, quantity FROM items WHERE name=? AND category=?"
        );
    query.addBindValue(item.GetName());
    query.addBindValue(item.GetCategory());

    if (!query.exec()) {
        qDebug() << "InsertItem check error:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        const int existingId  = query.value(0).toInt();
        const int newQuantity = query.value(1).toInt() + item.GetQuantity();

        QSqlQuery updateQuery(QSqlDatabase::database("main_connection"));
        updateQuery.prepare("UPDATE items SET quantity=? WHERE id=?");
        updateQuery.addBindValue(newQuantity);
        updateQuery.addBindValue(existingId);

        if (!updateQuery.exec()) {
            qDebug() << "InsertItem update error:" << updateQuery.lastError().text();
            return false;
        }
    } else {
        QSqlQuery insertQuery(QSqlDatabase::database("main_connection"));
        insertQuery.prepare(
            "INSERT INTO items (name, category, price, quantity) VALUES (?, ?, ?, ?)"
            );
        insertQuery.addBindValue(item.GetName());
        insertQuery.addBindValue(item.GetCategory());
        insertQuery.addBindValue(item.GetPrice());
        insertQuery.addBindValue(item.GetQuantity());

        if (!insertQuery.exec()) {
            qDebug() << "InsertItem error:" << insertQuery.lastError().text();
            return false;
        }
    }

    return true;
}

bool ItemDB::UpdateItem(const Item& item)
{
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    query.prepare(
        "UPDATE items SET name=?, category=?, price=?, quantity=? WHERE id=?"
        );

    query.addBindValue(item.GetName());
    query.addBindValue(item.GetCategory());
    query.addBindValue(item.GetPrice());
    query.addBindValue(item.GetQuantity());
    query.addBindValue(item.GetId());

    if (!query.exec()) {
        qDebug() << "UpdateItem error:" << query.lastError().text();
        return false;
    }

    return true;
}

bool ItemDB::DeleteItem(int id)
{
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    query.prepare("DELETE FROM items WHERE id=?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "DeleteItem error:" << query.lastError().text();
        return false;
    }

    return true;
}