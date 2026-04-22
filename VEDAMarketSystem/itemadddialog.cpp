#include "itemadddialog.h"
#include "ui_itemadddialog.h"
#include <QMessageBox>

ItemAddDialog::ItemAddDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemAddDialog) {
    ui->setupUi(this);
    setWindowTitle("제품 추가");

    // 버튼 클릭 시그널을 해당 슬롯에 연결
    connect(ui->AddButton, SIGNAL(clicked()), this, SLOT(onAddButton()));
    connect(ui->CancelButton, SIGNAL(clicked()), this, SLOT(onCancelButton()));
}

ItemAddDialog::~ItemAddDialog() {
    delete ui;
}

Item ItemAddDialog::getItem() const {
    // 현재 UI 입력값을 읽어 Item 객체를 구성하여 반환
    Item item;
    item.SetName(ui->NameEdit->text());
    item.SetCategory(ui->CategoryBox->currentText());
    item.SetPrice(ui->PriceEdit->text().toInt());
    item.SetQuantity(ui->QuantityEdit->text().toInt());
    return item;
}

void ItemAddDialog::onAddButton() {
    // 이름 입력 여부 확인
    if (ui->NameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "경고", "이름을 입력해주세요.");
        return;
    }

    // 가격 입력 여부 확인
    if (ui->PriceEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "경고", "가격을 입력해주세요.");
        return;
    }

    // 가격이 정수로 변환 가능한지 확인
    bool priceCheck;
    int price = ui->PriceEdit->text().trimmed().toInt(&priceCheck);
    if (!priceCheck) {
        QMessageBox::warning(this, "경고", "가격은 숫자만 입력해주세요.");
        return;
    }

    // 가격 음수 여부 확인
    if (price < 0) {
        QMessageBox::warning(this, "경고", "가격은 0 이상이어야 합니다.");
        return;
    }

    // 수량 입력 여부 확인
    if (ui->QuantityEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "경고", "수량을 입력해주세요.");
        return;
    }

    // 수량이 정수로 변환 가능한지 확인
    bool quantityCheck;
    int quantity = ui->QuantityEdit->text().trimmed().toInt(&quantityCheck);
    if (!quantityCheck) {
        QMessageBox::warning(this, "경고", "수량은 숫자만 입력해주세요.");
        return;
    }

    // 수량 음수 여부 확인
    if (quantity < 0) {
        QMessageBox::warning(this, "경고", "수량은 0 이상이어야 합니다.");
        return;
    }

    accept();
}

void ItemAddDialog::onCancelButton() {
    reject();
}