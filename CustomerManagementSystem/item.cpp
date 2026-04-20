#include "item.h"

Item::Item() {
}

Item::Item(int Id, QString Name, QString Category, int Price) {
    this->Id = Id;
    this->Name = Name;
    this->Category = Category;
    this->Price = Price;
}

int Item::GetId() const {
    return this->Id;
}
QString Item::GetName() const {
    return this->Name;
};
QString Item::GetCategory() const {
    return this->Category;
}
int Item::GetPrice() const {
    return this->Price;
}

void Item::SetId(int Id) {
    this->Id = Id;
}

void Item::SetName(QString Name) {
    this->Name = Name;
}

void Item::SetCategory(QString Category) {
    this->Category = Category;
}

void Item::SetPrice(int Price) {
    this->Price = Price;
}

