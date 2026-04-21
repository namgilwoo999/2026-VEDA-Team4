#ifndef SHOPWIDGET_H
#define SHOPWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include "itemdb.h"

namespace Ui {
class ShopWidget;
}

class ShopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShopWidget(QWidget *parent = nullptr);
    ~ShopWidget();
    void setUsername(const QString& username);

private slots:
    void onCategorySelected(QListWidgetItem* item);
    void onSearchTextChanged(const QString& text);
    void onDeleteItem();
    void onAddItem();
    void onModifyItem();
    void onProfileButton();

signals:
    void LogoutRequested();

private:
    void loadCards(const QList<Item>& items);
    Ui::ShopWidget* ui;
    ItemDB db;
    QString currentCategory = "전체";
    QString m_username;
};

#endif // SHOPWIDGET_H