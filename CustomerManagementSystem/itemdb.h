#ifndef ITEMDB_H
#define ITEMDB_H

#include "item.h"
#include <QList>

class ItemDB
{
public:
    ItemDB();

    QList<Item> GetAllItems();
    QList<Item> GetItemsByCategory(const QString& category);
    QList<Item> SearchItems(const QString& keyword, const QString& category = "전체");
    Item GetItemById(int id);

    bool InsertItem(const Item& item);
    bool UpdateItem(const Item& item);
    bool DeleteItem(int id);
};

#endif // ITEMDB_H