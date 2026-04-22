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
    // JSON 파일 경로
    const QString path = ":/items.json";
    QFile file(path);

    // 파일 열기 실패 시 경로를 출력하고 반환
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "JSON Not Open:" << path;
        return;
    }

    // 파일 전체를 읽어 JSON 문서로 파싱
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) return;

    // JSON 배열의 각 요소를 순회하며 Item으로 변환 후 DB에 삽입
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