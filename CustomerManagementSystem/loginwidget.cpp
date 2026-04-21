#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
    , m_signup(new SignupWidget())
{
    ui->setupUi(this);

    connect(ui->loginButton,  SIGNAL(clicked()), this, SLOT(OnLoginClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->signupButton, SIGNAL(clicked()), this, SLOT(OnSignupClicked()));

    connect(m_signup, SIGNAL(CancelRequested()), m_signup, SLOT(hide()));
    connect(m_signup, SIGNAL(CancelRequested()), this, SLOT(show()));
}

LoginWidget::~LoginWidget()
{
    delete ui;
    delete m_signup;
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
    this->hide();
    m_signup->show();
}
