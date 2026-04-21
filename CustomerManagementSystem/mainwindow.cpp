#include "mainwindow.h"
#include "mypage.h"
#include "shopwidget.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_loginWidget(new LoginWidget(this))
    , m_shopWidget(new ShopWidget(this))
    , m_signupWidget(new SignupWidget(this)) {
    ui->setupUi(this);

    ui->stackedWidget->addWidget(m_loginWidget);  // index 0
    ui->stackedWidget->addWidget(m_shopWidget);   // index 1
    ui->stackedWidget->addWidget(m_signupWidget); // index 2
    ui->stackedWidget->setCurrentIndex(0);

    connect(m_loginWidget, SIGNAL(LoginRequested(QString, QString)),
            this, SLOT(OnLoginRequested(QString, QString)));
    connect(m_loginWidget, SIGNAL(SignUpRequested()),
            this, SLOT(OnSignUpRequested()));
    connect(m_signupWidget, SIGNAL(SignupCompleted()),
            this, SLOT(OnSignupCompleted()));         // 가입 완료 → 로그인 화면
    connect(m_signupWidget, SIGNAL(CancelRequested()),
            this, SLOT(OnSignUpCancelled()));         // 취소 → 로그인 화면
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::OnLoginRequested(const QString &id, const QString &password) {
    if (m_userDb.VerifyPassword(id, password)) {
        m_shopWidget->setUsername(id);
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        QMessageBox::warning(this, "로그인 실패", "아이디 또는 비밀번호가 올바르지 않습니다.");
    }
}

void MainWindow::OnSignUpRequested()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::OnSignupCompleted()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::OnSignUpCancelled()
{
    ui->stackedWidget->setCurrentIndex(0);
}

