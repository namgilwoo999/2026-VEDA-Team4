#include <QString>
#ifndef ITEM_H
#define ITEM_H

class Item {
private:
    int Id;
    QString Name;
    QString Category;
    int Price;
public:
    Item();
    Item(int Id, QString Name, QString Category, int Price);

    int GetId() const;
    QString GetName() const;
    QString GetCategory() const;
    int GetPrice() const;

    void SetId(int Id);
    void SetName(QString Name);
    void SetCategory(QString Category);
    void SetPrice(int Price);
};

#endif // ITEM_H
