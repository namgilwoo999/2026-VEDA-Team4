#include "mainwindow.h"
#include "mypage.h"
#include "shopwidget.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_loginWidget(new LoginWidget())
    , m_shopWidget(new ShopWidget()) {
    ui->setupUi(this);

    connect(m_loginWidget, SIGNAL(LoginRequested(QString, QString)),
            this, SLOT(OnLoginRequested(QString, QString)));
    m_loginWidget->show();
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_loginWidget;
    delete m_shopWidget;
}

void MainWindow::OnLoginRequested(const QString &id, const QString &password) {
    if (m_userDb.VerifyPassword(id, password)) {
        m_loginWidget->hide();
        m_shopWidget->show();
    } else {
        QMessageBox::warning(m_loginWidget, "로그인 실패", "아이디 또는 비밀번호가 올바르지 않습니다.");
    }
}
