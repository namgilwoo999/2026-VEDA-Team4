#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_loginWidget(new LoginWidget(this))
    , m_shopWidget(new ShopWidget(this))
    , m_signupWidget(new SignupWidget(this)) {
    ui->setupUi(this);

    // 스택 위젯에 화면 순서대로 추가 index 0=로그인, 1=쇼핑, 2=회원가입
    ui->stackedWidget->addWidget(m_loginWidget);
    ui->stackedWidget->addWidget(m_shopWidget);
    ui->stackedWidget->addWidget(m_signupWidget);
    ui->stackedWidget->setCurrentIndex(0);

    // 화면 전환 신호 연결
    connect(m_loginWidget, SIGNAL(LoginRequested(QString, QString)),
            this, SLOT(OnLoginRequested(QString, QString)));
    connect(m_loginWidget, SIGNAL(SignUpRequested()),
            this, SLOT(OnSignUpRequested()));
    connect(m_signupWidget, SIGNAL(SignupCompleted()),
            this, SLOT(OnSignupCompleted()));
    connect(m_signupWidget, SIGNAL(CancelRequested()),
            this, SLOT(OnSignUpCancelled()));
    connect(m_shopWidget, SIGNAL(LogoutRequested()),
            this, SLOT(OnLogoutRequested()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::OnLoginRequested(const QString &id, const QString &password) {
    // 자격 증명 검증 후 성공 시 쇼핑 화면으로 전환, 실패 시 경고 표시
    if (m_userDb.VerifyPassword(id, password)) {
        m_shopWidget->setUsername(id);
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        QMessageBox::warning(this, "로그인 실패", "아이디 또는 비밀번호가 올바르지 않습니다.");
    }
}

void MainWindow::OnSignUpRequested() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::OnSignupCompleted() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::OnSignUpCancelled() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::OnLogoutRequested() {
    ui->stackedWidget->setCurrentIndex(0);
}
