#include "mainwindow.h"
#include "mypage.h"
#include "shopwidget.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_loginWidget(new LoginWidget(this))
    , m_shopWidget(new ShopWidget(this)) {
    ui->setupUi(this);

    ui->stackedWidget->addWidget(m_loginWidget);  // index 0
    ui->stackedWidget->addWidget(m_shopWidget);   // index 1
    ui->stackedWidget->setCurrentIndex(0);

    connect(m_loginWidget, SIGNAL(LoginRequested(QString, QString)),
            this, SLOT(OnLoginRequested(QString, QString)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::OnLoginRequested(const QString &id, const QString &password) {
    if (m_userDb.VerifyPassword(id, password)) {
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        QMessageBox::warning(this, "로그인 실패", "아이디 또는 비밀번호가 올바르지 않습니다.");
    }
}
