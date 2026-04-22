#include "itemmodifydialog.h"
#include "ui_itemmodifydialog.h"
#include <QMessageBox>

ItemModifyDialog::ItemModifyDialog(const Item& item, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemModifyDialog) {

    ui->setupUi(this);
    setWindowTitle("제품 수정");

    // 전달받은 item의 기존 값을 각 입력 위젯에 미리 채워 표시
    ui->NameEdit->setText(item.GetName());
    ui->CategoryBox->setCurrentText(item.GetCategory());
    ui->PriceEdit->setText(QString::number(item.GetPrice()));
    ui->QuantityEdit->setText(QString::number(item.GetQuantity()));

    // 버튼 클릭 시그널을 해당 슬롯에 연결
    connect(ui->Modify, SIGNAL(clicked()), this, SLOT(onModifyButton()));
    connect(ui->Cancel, SIGNAL(clicked()), this, SLOT(onCancelButton()));
}

ItemModifyDialog::~ItemModifyDialog() {
    delete ui;
}

Item ItemModifyDialog::getItem() const {
    // 현재 UI 입력값을 읽어 Item 객체를 구성하여 반환
    Item item;
    item.SetName(ui->NameEdit->text());
    item.SetCategory(ui->CategoryBox->currentText());
    item.SetPrice(ui->PriceEdit->text().toInt());
    item.SetQuantity(ui->QuantityEdit->text().toInt());
    return item;
}

void ItemModifyDialog::onModifyButton() {
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

void ItemModifyDialog::onCancelButton() {
    reject();
}