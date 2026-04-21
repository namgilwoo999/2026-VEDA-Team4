#include "itemseed.h"
#include "itemdb.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDebug>

void ItemSeed::load(ItemDB& db)
{
    const QString path = QCoreApplication::applicationDirPath() + "/items.json";
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "JSON Not Open:" << path;
        return;
    }

    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) return;

    const QJsonArray arr = doc.array();
    for (const QJsonValue& v : arr) {
        const QJsonObject obj = v.toObject();
        Item item;
        item.SetName(obj["name"].toString());
        item.SetCategory(obj["category"].toString());
        item.SetPrice(obj["price"].toInt());
        item.SetQuantity(obj["quantity"].toInt());
        db.InsertItem(item);
    }
}