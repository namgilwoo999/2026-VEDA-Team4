#include <QString>
#ifndef ITEM_H
#define ITEM_H

class Item {
private:
    int id;
    QString name;
    QString category;
    int price;
    int quantity;

public:
    Item();
    Item(int id, QString name, QString category, int price, int quantity);

    int GetId() const;
    QString GetName() const;
    QString GetCategory() const;
    int GetPrice() const;
    int GetQuantity() const;

    void SetId(int id);
    void SetName(QString name);
    void SetCategory(QString category);
    void SetPrice(int price);
    void SetQuantity(int quantity);
};

#endif // ITEM_H