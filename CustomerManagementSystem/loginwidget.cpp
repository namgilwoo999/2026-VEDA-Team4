#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    connect(ui->loginButton,  SIGNAL(clicked()), this, SLOT(OnLoginClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(OnCancelClicked()));
    connect(ui->signupButton, SIGNAL(clicked()), this, SLOT(OnSignupClicked()));
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::OnLoginClicked()
{
    emit LoginRequested(ui->idLineEdit->text(), ui->passwordLineEdit->text());
}

void LoginWidget::OnCancelClicked()
{
    emit CancelRequested();
}

void LoginWidget::OnSignupClicked()
{
    emit SignupRequested();
}
