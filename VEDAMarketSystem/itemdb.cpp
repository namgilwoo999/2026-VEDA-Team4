#include "itemdb.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ItemDB::ItemDB() {}

QList<Item> ItemDB::GetAllItems() {
    // Item 저장 리스트
    QList<Item> list;

    // "main_connection"에 바인딩
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    // 전체 상품 조회
    if (!query.exec("SELECT id, name, category, price, quantity FROM items")) {
        qDebug() << "Query error:" << query.lastError().text();
        return list;
    }

    // Item 객체로 변환 후 리스트에 추가
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

QList<Item> ItemDB::GetItemsByCategory(const QString& category) {
    // "전체" 카테고리 모든 아이템 반환
    if (category == "전체")
        return GetAllItems();

    // Item 저장 리스트
    QList<Item> list;
    // "main_conecction"에 바인딩
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    // SQL 인젝션 방지
    query.prepare(
        "SELECT id, name, category, price, quantity FROM items WHERE category=?"
        );
    query.addBindValue(category);

    // 쿼리 실행 실패 시 빈 리스트 반환
    if (!query.exec()) {
        qDebug() << "GetItemsByCategory error:" << query.lastError().text();
        return list;
    }

    // Item 객체로 변환 후 리스트에 추가
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

QList<Item> ItemDB::SearchItems(const QString& keyword, const QString& category) {
    QList<Item> list;
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    // "%keyword%" 형태로 부분 일치 검색
    const QString pattern = "%" + keyword + "%";

    if (category == "전체") {
        // 전체 카테고리 내에서 name 또는 category 검색
        query.prepare(
            "SELECT id, name, category, price, quantity FROM items "
            "WHERE name LIKE ? OR category LIKE ?"
            );
        query.addBindValue(pattern);
        query.addBindValue(pattern);
    } else {
        // 특정 카테고리 내에서 name 검색
        query.prepare(
            "SELECT id, name, category, price, quantity FROM items "
            "WHERE (name LIKE ? OR category LIKE ?) AND category = ?"
            );
        query.addBindValue(pattern);
        query.addBindValue(pattern);
        query.addBindValue(category);
    }

    // 쿼리 실행 실패 시 빈 리스트 반환
    if (!query.exec()) {
        qDebug() << "SearchItems error:" << query.lastError().text();
        return list;
    }

    // Item 객체로 변환 후 리스트에 추가
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

Item ItemDB::GetItemById(int id) {
    Item item;

    QSqlQuery query(QSqlDatabase::database("main_connection"));

    // id를 바인딩하여 조회
    query.prepare("SELECT id, name, category, price, quantity FROM items WHERE id=?");
    query.addBindValue(id);

    // 쿼리 실행 실패 시 기본값 Item 반환
    if (!query.exec()) {
        qDebug() << "GetItemById error:" << query.lastError().text();
        return item;
    }

    // 결과가 존재하면 Item 반환
    if (query.next()) {
        item.SetId(query.value(0).toInt());
        item.SetName(query.value(1).toString());
        item.SetCategory(query.value(2).toString());
        item.SetPrice(query.value(3).toInt());
        item.SetQuantity(query.value(4).toInt());
    }

    return item;
}

bool ItemDB::InsertItem(const Item& item) {
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    // 동일한 name + category 존재하는지 확인
    query.prepare(
        "SELECT id, quantity FROM items WHERE name=? AND category=?"
        );
    query.addBindValue(item.GetName());
    query.addBindValue(item.GetCategory());

    // 쿼리 실행 실패 시 false 반환
    if (!query.exec()) {
        qDebug() << "InsertItem check error:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        // 중복 상품이 존재하면 기존 수량에 추가 수량을 합산
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
        // 중복 상품이 없으면 INSERT
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

    // 해당 Item의 필드를 갱신
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

    // id에 해당하는 Item 삭제
    query.prepare("DELETE FROM items WHERE id=?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "DeleteItem error:" << query.lastError().text();
        return false;
    }

    return true;
}