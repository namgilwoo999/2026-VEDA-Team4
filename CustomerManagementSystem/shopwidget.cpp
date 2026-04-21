#include "shopwidget.h"
#include "ui_shopwidget.h"
#include "itemadddialog.h"
#include "itemmodifydialog.h"
#include "mypage.h"

ShopWidget::ShopWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShopWidget)
{
    ui->setupUi(this);

    connect(ui->CategoryList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onCategorySelected(QListWidgetItem*)));
    connect(ui->SearchBar, SIGNAL(textChanged(QString)), this, SLOT(onSearchTextChanged(QString)));
    connect(ui->DeleteButton, SIGNAL(clicked()), this, SLOT(onDeleteItem()));
    connect(ui->AddButton, SIGNAL(clicked()), this, SLOT(onAddItem()));
    connect(ui->modifyButton, SIGNAL(clicked()), this, SLOT(onModifyItem()));
    connect(ui->ProfileButton, SIGNAL(clicked()), this, SLOT(onProfileButton()));

    loadCards(db.GetAllItems());
}

ShopWidget::~ShopWidget()
{
    delete ui;
}

void ShopWidget::onCategorySelected(QListWidgetItem* item)
{
    currentCategory = item->text();
    const QString keyword = ui->SearchBar->text().trimmed();
    if (!keyword.isEmpty()) {
        loadCards(db.SearchItems(keyword, currentCategory));  // currentCategory 추가
    } else {
        loadCards(db.GetItemsByCategory(currentCategory));
    }
}

void ShopWidget::onSearchTextChanged(const QString& text)
{
    if (text.trimmed().isEmpty()) {
        loadCards(db.GetItemsByCategory(currentCategory));
    } else {
        loadCards(db.SearchItems(text.trimmed(), currentCategory));  // currentCategory 추가
    }
}

void ShopWidget::loadCards(const QList<Item>& items)
{
    ui->ItemCardList->clear();

    for (const Item& item : items) {
        QString text = QString(
                           "%1\n"
                           "카테고리: %2\n"
                           "가격: ₩%3\n"
                           "수량: %4"
                           ).arg(item.GetName())
                           .arg(item.GetCategory())
                           .arg(item.GetPrice())
                           .arg(item.GetQuantity());

        QListWidgetItem* listItem = new QListWidgetItem(text);
        listItem->setData(Qt::UserRole, item.GetId());
        ui->ItemCardList->addItem(listItem);
    }
}

void ShopWidget::onDeleteItem()
{
    QListWidgetItem* selected = ui->ItemCardList->currentItem();
    if (!selected) {
        QMessageBox::warning(this, "경고", "삭제할 제품을 선택해주세요.");
        return;
    }

    const int id = selected->data(Qt::UserRole).toInt();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "삭제 확인", "정말 삭제하시겠습니까?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        db.DeleteItem(id);
        loadCards(db.GetItemsByCategory(currentCategory));
    }
}

void ShopWidget::onAddItem()
{
    ItemAddDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        db.InsertItem(dlg.getItem());
        loadCards(db.GetItemsByCategory(currentCategory));
    }
}

void ShopWidget::onModifyItem()
{
    QListWidgetItem* selected = ui->ItemCardList->currentItem();
    if (!selected) {
        QMessageBox::warning(this, "경고", "수정할 제품을 선택해주세요.");
        return;
    }

    const int id = selected->data(Qt::UserRole).toInt();
    Item item = db.GetItemById(id);

    ItemModifyDialog dlg(item, this);
    if (dlg.exec() == QDialog::Accepted) {
        Item updated = dlg.getItem();
        updated.SetId(id);
        db.UpdateItem(updated);
        loadCards(db.GetItemsByCategory(currentCategory));
    }
}

void ShopWidget::setUsername(const QString& username)
{
    m_username = username;
}

void ShopWidget::onProfileButton()
{
    Mypage dlg(m_username, this);
    connect(&dlg, SIGNAL(LogoutRequested()), this, SIGNAL(LogoutRequested()));
    connect(&dlg, SIGNAL(AccountDeleted()), this, SIGNAL(LogoutRequested()));
    dlg.exec();
}