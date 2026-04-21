#include "mypage.h"
#include "ui_mypage.h"
#include <QMessageBox>

Mypage::Mypage(const QString &username, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mypage)
    , m_username(username) {
    ui->setupUi(this);

    connect(ui->menuListWidget,       SIGNAL(currentRowChanged(int)), this, SLOT(OnMenuItemClicked(int)));
    connect(ui->menuListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(OnMenuItemClicked(int)));
    connect(ui->changePasswordButton, SIGNAL(clicked()), this, SLOT(OnChangePasswordClicked()));
    connect(ui->cancelPasswordButton, SIGNAL(clicked()), this, SLOT(OnCancelPasswordClicked()));
    connect(ui->confirmDeleteButton,  SIGNAL(clicked()), this, SLOT(OnConfirmDeleteClicked()));
    connect(ui->cancelDeleteButton,   SIGNAL(clicked()), this, SLOT(OnCancelDeleteClicked()));
    connect(ui->LogoutButton, SIGNAL(clicked()), this, SLOT(OnLogoutClicked()));
    ui->menuListWidget->setCurrentRow(0);
}

Mypage::~Mypage() {
    delete ui;
}

void Mypage::OnMenuItemClicked(int row) {
    ui->stackedWidget->setCurrentIndex(row);
}

void Mypage::OnChangePasswordClicked() {
    QString currentPw = ui->currentPasswordLineEdit->text();
    QString newPw     = ui->newPasswordLineEdit->text();
    QString confirmPw = ui->confirmPasswordLineEdit->text();

    if (currentPw.isEmpty() || newPw.isEmpty() || confirmPw.isEmpty()) {
        QMessageBox::warning(this, "알림", "모든 항목을 입력해주세요.");
        return;
    }

    if (!m_userDb.VerifyPassword(m_username, currentPw)) {
        QMessageBox::warning(this, "오류", "현재 비밀번호가 일치하지 않습니다.");
        ui->currentPasswordLineEdit->clear();
        ui->currentPasswordLineEdit->setFocus();
        return;
    }

    if (newPw != confirmPw) {
        QMessageBox::warning(this, "오류", "새로운 비밀번호가 일치하지 않습니다.");
        ui->newPasswordLineEdit->clear();
        ui->confirmPasswordLineEdit->clear();
        ui->newPasswordLineEdit->setFocus();
        return;
    }

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
    if (m_userDb.DeleteUser(m_username)) {
        QMessageBox::information(this, "알림", "회원탈퇴가 완료되었습니다.");
        emit AccountDeleted();
        this->close();
    } else {
        QMessageBox::critical(this, "오류", "회원탈퇴 중 오류가 발생했습니다.");
    }
}

void Mypage::OnCancelPasswordClicked() {
    ui->currentPasswordLineEdit->clear();
    ui->newPasswordLineEdit->clear();
    ui->confirmPasswordLineEdit->clear();
}

void Mypage::OnCancelDeleteClicked() {
    ui->menuListWidget->setCurrentRow(0);
}

void Mypage::OnLogoutClicked()
{
    QMessageBox::information(this, "로그아웃", "로그아웃 되었습니다.");
    emit LogoutRequested();
    this->close();
}
