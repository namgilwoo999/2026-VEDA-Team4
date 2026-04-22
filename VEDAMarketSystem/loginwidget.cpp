#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget) {
    ui->setupUi(this);

    // 버튼 클릭 신호와 슬롯 연결
    connect(ui->loginButton,  SIGNAL(clicked()), this, SLOT(OnLoginClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->signupButton, SIGNAL(clicked()), this, SLOT(OnSignUpClicked()));
}

LoginWidget::~LoginWidget() {
    delete ui;
}

void LoginWidget::OnSignUpClicked() {
    emit SignUpRequested();
}

void LoginWidget::OnLoginClicked() {
    // 입력값을 신호로 전달한 뒤 보안을 위해 필드 즉시 초기화
    emit LoginRequested(ui->idLineEdit->text(), ui->passwordLineEdit->text());

    ui->idLineEdit->clear();
    ui->passwordLineEdit->clear();
}
