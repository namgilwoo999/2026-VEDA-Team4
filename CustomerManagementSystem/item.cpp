#include "item.h"

Item::Item() {
}

Item::Item(int id, QString name, QString category, int price) {
    this->id = id;
    this->name = name;
    this->category = category;
    this->price = price;
}

int Item::GetId() const {
    return this->id;
}
QString Item::GetName() const {
    return this->name;
};
QString Item::GetCategory() const {
    return this->category;
}
int Item::GetPrice() const {
    return this->price;
}

void Item::SetId(int id) {
    this->id = id;
}

void Item::SetName(QString name) {
    this->name = name;
}

void Item::SetCategory(QString category) {
    this->category = category;
}

void Item::SetPrice(int price) {
    this->price = price;
}

