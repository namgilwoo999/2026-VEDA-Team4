#include "itemadddialog.h"
#include "ui_itemadddialog.h"
#include <QMessageBox>

ItemAddDialog::ItemAddDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemAddDialog)
{
    ui->setupUi(this);
    setWindowTitle("제품 추가");

    connect(ui->AddButton, SIGNAL(clicked()), this, SLOT(onAddButton()));
    connect(ui->CancelButton, SIGNAL(clicked()), this, SLOT(onCancelButton()));
}

ItemAddDialog::~ItemAddDialog()
{
    delete ui;
}

Item ItemAddDialog::getItem() const
{
    Item item;
    item.SetName(ui->NameEdit->text());
    item.SetCategory(ui->CategoryBox->currentText());
    item.SetPrice(ui->PriceEdit->text().toInt());
    item.SetQuantity(ui->QuantityEdit->text().toInt());
    return item;
}

void ItemAddDialog::onAddButton()
{
    if (ui->NameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "경고", "이름을 입력해주세요.");
        return;
    }
    if (ui->PriceEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "경고", "가격을 입력해주세요.");
        return;
    }
    bool priceCheck;
    int price = ui->PriceEdit->text().trimmed().toInt(&priceCheck);
    if (!priceCheck) {
        QMessageBox::warning(this, "경고", "가격은 숫자만 입력해주세요.");
        return;
    }
    if (price < 0) {
        QMessageBox::warning(this, "경고", "가격은 0 이상이어야 합니다.");
        return;
    }
    if (ui->QuantityEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "경고", "수량을 입력해주세요.");
        return;
    }
    bool quantityCheck;
    int quantity = ui->QuantityEdit->text().trimmed().toInt(&quantityCheck);
    if (!quantityCheck) {
        QMessageBox::warning(this, "경고", "수량은 숫자만 입력해주세요.");
        return;
    }
    if (quantity < 0) {
        QMessageBox::warning(this, "경고", "수량은 0 이상이어야 합니다.");
        return;
    }

    accept();
}

void ItemAddDialog::onCancelButton()
{
    reject();
}