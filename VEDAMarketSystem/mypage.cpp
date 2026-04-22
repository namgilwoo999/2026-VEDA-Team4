#include "mypage.h"
#include "ui_mypage.h"
#include <QMessageBox>

Mypage::Mypage(const QString &username, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mypage)
    , m_username(username) {
    ui->setupUi(this);

    // 메뉴 및 버튼 신호 연결
    connect(ui->menuListWidget,       SIGNAL(currentRowChanged(int)), this, SLOT(OnMenuItemClicked(int)));
    connect(ui->changePasswordButton, SIGNAL(clicked()), this, SLOT(OnChangePasswordClicked()));
    connect(ui->cancelPasswordButton, SIGNAL(clicked()), this, SLOT(OnCancelPasswordClicked()));
    connect(ui->confirmDeleteButton,  SIGNAL(clicked()), this, SLOT(OnConfirmDeleteClicked()));
    connect(ui->cancelDeleteButton,   SIGNAL(clicked()), this, SLOT(OnCancelDeleteClicked()));
    connect(ui->LogoutButton,  SIGNAL(clicked()), this, SLOT(OnLogoutClicked()));
    connect(ui->CancelButton,  SIGNAL(clicked()), this, SLOT(OnCancelLogoutClicked()));

    // 첫 번째 메뉴 항목(비밀번호 변경) 기본 선택
    ui->menuListWidget->setCurrentRow(0);
}

Mypage::~Mypage() {
    delete ui;
}

void Mypage::OnMenuItemClicked(int row) {
    // 선택된 메뉴 행 인덱스와 동일한 스택 페이지로 전환
    ui->stackedWidget->setCurrentIndex(row);
}

void Mypage::OnChangePasswordClicked() {
    QString currentPw = ui->currentPasswordLineEdit->text();
    QString newPw     = ui->newPasswordLineEdit->text();
    QString confirmPw = ui->confirmPasswordLineEdit->text();

    // 빈 항목 검사
    if (currentPw.isEmpty() || newPw.isEmpty() || confirmPw.isEmpty()) {
        QMessageBox::warning(this, "알림", "모든 항목을 입력해주세요.");
        return;
    }

    // 현재 비밀번호 일치 여부 확인
    if (!m_userDb.VerifyPassword(m_username, currentPw)) {
        QMessageBox::warning(this, "오류", "현재 비밀번호가 일치하지 않습니다.");
        ui->currentPasswordLineEdit->clear();
        ui->currentPasswordLineEdit->setFocus();
        return;
    }

    // 새 비밀번호와 확인란 일치 여부 검사
    if (newPw != confirmPw) {
        QMessageBox::warning(this, "오류", "새로운 비밀번호가 일치하지 않습니다.");
        ui->newPasswordLineEdit->clear();
        ui->confirmPasswordLineEdit->clear();
        ui->newPasswordLineEdit->setFocus();
        return;
    }

    // DB 업데이트 후 입력 필드 초기화
    if (m_userDb.UpdatePassword(m_username, newPw)) {
        QMessageBox::information(this, "알림", "비밀번호가 변경되었습니다.");
        ui->currentPasswordLineEdit->clear();
        ui->newPasswordLineEdit->clear();
        ui->confirmPasswordLineEdit->clear();
    } else {
        QMessageBox::critical(this, "오류", "비밀번호 변경 중 오류가 발생했습니다.");
    }
}

void Mypage::OnConfirmDeleteClicked() {
    // 실수 방지를 위한 이중 확인 (기본 선택: No)
    QMessageBox::StandardButton reply = QMessageBox::warning(
        this, "회원탈퇴 확인",
        "정말로 탈퇴하시겠습니까?\n탈퇴 후에는 복구할 수 없습니다.",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );

    if (reply != QMessageBox::Yes) {
        return;
    }

    // 탈퇴 처리 후 신호 발생으로 로그인 화면 복귀
    if (m_userDb.DeleteUser(m_username)) {
        QMessageBox::information(this, "알림", "회원탈퇴가 완료되었습니다.");
        emit AccountDeleted();
        this->close();
    } else {
        QMessageBox::critical(this, "오류", "회원탈퇴 중 오류가 발생했습니다.");
    }
}

void Mypage::OnCancelPasswordClicked() {
    // 입력 필드 초기화 후 다이얼로그 닫기
    ui->currentPasswordLineEdit->clear();
    ui->newPasswordLineEdit->clear();
    ui->confirmPasswordLineEdit->clear();
    reject();
}

void Mypage::OnCancelDeleteClicked() {
    // 다이얼로그 닫기
    reject();
}

void Mypage::OnLogoutClicked() {
    QMessageBox::information(this, "로그아웃", "로그아웃 되었습니다.");
    emit LogoutRequested();
    this->close();
}

void Mypage::OnCancelLogoutClicked() {
    reject();
}
