#include "shopwidget.h"
#include "ui_shopwidget.h"
#include "itemadddialog.h"
#include "itemmodifydialog.h"
#include "mypage.h"

ShopWidget::ShopWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShopWidget) {
    ui->setupUi(this);

    // 각 UI 요소의 시그널을 해당 슬롯에 연결
    connect(ui->CategoryList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onCategorySelected(QListWidgetItem*)));
    connect(ui->SearchBar, SIGNAL(textChanged(QString)), this, SLOT(onSearchTextChanged(QString)));
    connect(ui->DeleteButton, SIGNAL(clicked()), this, SLOT(onDeleteItem()));
    connect(ui->AddButton, SIGNAL(clicked()), this, SLOT(onAddItem()));
    connect(ui->modifyButton, SIGNAL(clicked()), this, SLOT(onModifyItem()));
    connect(ui->ProfileButton, SIGNAL(clicked()), this, SLOT(onProfileButton()));

    // 초기 화면에 전체 상품 목록 로드
    loadCards(db.GetAllItems());
}

ShopWidget::~ShopWidget() {
    delete ui;
}

void ShopWidget::onCategorySelected(QListWidgetItem* item) {
    // 클릭된 카테고리 항목의 텍스트로 현재 카테고리 갱신
    currentCategory = item->text();

    const QString keyword = ui->SearchBar->text().trimmed();

    // 검색어가 있으면 카테고리 + 키워드 복합 검색, 없으면 카테고리 단독 필터
    if (!keyword.isEmpty()) {
        loadCards(db.SearchItems(keyword, currentCategory));
    } else {
        loadCards(db.GetItemsByCategory(currentCategory));
    }
}

void ShopWidget::onSearchTextChanged(const QString& text) {
    // 검색어가 비어 있으면 현재 카테고리의 전체 목록 복원
    if (text.trimmed().isEmpty()) {
        loadCards(db.GetItemsByCategory(currentCategory));
    } else {
        // 검색어가 있으면 현재 카테고리 범위 내에서 키워드 검색
        loadCards(db.SearchItems(text.trimmed(), currentCategory));
    }
}

void ShopWidget::loadCards(const QList<Item>& items) {
    // 기존 카드 목록 초기화
    ui->ItemCardList->clear();

    for (const Item& item : items) {
        // 각 Item 정보를 여러 줄 텍스트로 구성
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

        // 선택 시 수정 및 삭제를 위해 id를 식별할 수 있도록 UserRole에 item id 저장
        listItem->setData(Qt::UserRole, item.GetId());
        ui->ItemCardList->addItem(listItem);
    }
}

void ShopWidget::onDeleteItem() {
    // 선택된 항목이 없으면 경고 후 반환
    QListWidgetItem* selected = ui->ItemCardList->currentItem();
    if (!selected) {
        QMessageBox::warning(this, "경고", "삭제할 제품을 선택해주세요.");
        return;
    }

    // UserRole에 저장된 id를 꺼내 삭제 대상 특정
    const int id = selected->data(Qt::UserRole).toInt();

    // 삭제 전 사용자 확인 다이얼로그 표시
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "삭제 확인", "정말 삭제하시겠습니까?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // 확인 시 DB에서 삭제 후 현재 카테고리 기준으로 목록 갱신
        db.DeleteItem(id);
        loadCards(db.GetItemsByCategory(currentCategory));
    }
}

void ShopWidget::onAddItem() {
    // 상품 추가 다이얼로그 실행
    ItemAddDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        // Accepted 시 입력된 Item을 DB에 삽입하고 목록 갱신
        db.InsertItem(dlg.getItem());
        loadCards(db.GetItemsByCategory(currentCategory));
    }
}

void ShopWidget::onModifyItem() {
    // 선택된 항목이 없으면 경고 후 반환
    QListWidgetItem* selected = ui->ItemCardList->currentItem();
    if (!selected) {
        QMessageBox::warning(this, "경고", "수정할 제품을 선택해주세요.");
        return;
    }

    // UserRole에 저장된 id로 DB에서 기존 Item 조회
    const int id = selected->data(Qt::UserRole).toInt();
    Item item = db.GetItemById(id);

    // 기존 값을 채운 수정 다이얼로그 실행
    ItemModifyDialog dlg(item, this);
    if (dlg.exec() == QDialog::Accepted) {
        // 수정된 Item에 원래 id를 유지한 뒤 DB 업데이트 후 목록 갱신
        Item updated = dlg.getItem();
        updated.SetId(id);
        db.UpdateItem(updated);
        loadCards(db.GetItemsByCategory(currentCategory));
    }
}

void ShopWidget::setUsername(const QString& username) {
    // 로그인한 사용자 이름을 멤버 변수에 저장
    m_username = username;
}

void ShopWidget::onProfileButton() {
    // 저장된 사용자 이름으로 마이페이지 다이얼로그 생성
    Mypage dlg(m_username, this);

    // 로그아웃 / 회원탈퇴 시그널을 상위 위젯으로 전파
    connect(&dlg, SIGNAL(LogoutRequested()), this, SIGNAL(LogoutRequested()));
    connect(&dlg, SIGNAL(AccountDeleted()), this, SIGNAL(LogoutRequested()));
    dlg.exec();
}