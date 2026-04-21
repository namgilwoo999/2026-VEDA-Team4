#include <QString>
#ifndef ITEM_H
#define ITEM_H

class Item {
private:
    int id;
    QString name;
    QString category;
    int price;

public:
    Item();
    Item(int id, QString name, QString category, int price);

    int GetId() const;
    QString GetName() const;
    QString GetCategory() const;
    int GetPrice() const;

    void SetId(int id);
    void SetName(QString name);
    void SetCategory(QString category);
    void SetPrice(int price);
};

#endif // ITEM_H