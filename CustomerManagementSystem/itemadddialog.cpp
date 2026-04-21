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
    item.SetQuantity(ui->lineEdit_3->text().toInt());
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
    if (ui->lineEdit_3->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "경고", "수량을 입력해주세요.");
        return;
    }

    accept();
}

void ItemAddDialog::onCancelButton()
{
    reject();
}