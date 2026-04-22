#include "itemmodifydialog.h"
#include "ui_itemmodifydialog.h"
#include <QMessageBox>

ItemModifyDialog::ItemModifyDialog(const Item& item, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemModifyDialog)
{
    ui->setupUi(this);
    setWindowTitle("제품 수정");

    // 기존 값 채우기
    ui->NameEdit->setText(item.GetName());
    ui->CategoryBox->setCurrentText(item.GetCategory());
    ui->PriceEdit->setText(QString::number(item.GetPrice()));
    ui->QuantityEdit->setText(QString::number(item.GetQuantity()));

    connect(ui->Modify, SIGNAL(clicked()), this, SLOT(onModifyButton()));
    connect(ui->Cancel, SIGNAL(clicked()), this, SLOT(onCancelButton()));
}

ItemModifyDialog::~ItemModifyDialog()
{
    delete ui;
}

Item ItemModifyDialog::getItem() const
{
    Item item;
    item.SetName(ui->NameEdit->text());
    item.SetCategory(ui->CategoryBox->currentText());
    item.SetPrice(ui->PriceEdit->text().toInt());
    item.SetQuantity(ui->QuantityEdit->text().toInt());
    return item;
}

void ItemModifyDialog::onModifyButton()
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

void ItemModifyDialog::onCancelButton()
{
    reject();
}