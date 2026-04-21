#include "signupwidget.h"
#include "ui_signupwidget.h"
#include "user.h"
#include <QMessageBox>

SignupWidget::SignupWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignupWidget)
{
    ui->setupUi(this);

    connect(ui->checkIdButton, SIGNAL(clicked()), this, SLOT(OnCheckIdClicked()));
    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(OnConfirmClicked()));
    connect(ui->cancelButton,  SIGNAL(clicked()), this, SLOT(OnCancelClicked()));
}

SignupWidget::~SignupWidget()
{
    delete ui;
}

void SignupWidget::OnCheckIdClicked()
{
    QString id = ui->idLineEdit->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "알림", "아이디를 입력해주세요.");
        return;
    }

    if (m_userDb.UsernameExists(id)) {
        QMessageBox::warning(this, "중복 확인", "이미 사용 중인 아이디입니다.\n다른 아이디를 입력해주세요.");
        ui->idLineEdit->clear();
        ui->idLineEdit->setFocus();
        m_idChecked = false;
    } else {
        QMessageBox::information(this, "중복 확인", "사용 가능한 아이디입니다.");
        m_idChecked = true;
    }
}

void SignupWidget::OnConfirmClicked()
{
    if (!m_idChecked) {
        QMessageBox::warning(this, "알림", "아이디 중복 확인을 해주세요.");
        return;
    }

    QString id       = ui->idLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString name     = ui->nameLineEdit->text().trimmed();
    QDate   birth    = ui->birthDateEdit->date();
    QString phone    = ui->phoneLineEdit->text().trimmed();
    QString email    = ui->emailLineEdit->text().trimmed();

    if (id.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "알림", "아이디와 비밀번호는 필수 입력입니다.");
        return;
    }

    User newUser(id, password, name, birth, phone,
                 ui->phoneAlarmCheckBox->isChecked(),
                 email, ui->emailAlarmCheckBox->isChecked());

    if (m_userDb.AddUser(newUser)) {
        QMessageBox::information(this, "회원가입", "회원가입이 완료되었습니다.");
        emit SignupCompleted();
        this->close();
    } else {
        QMessageBox::critical(this, "오류", "회원가입 중 오류가 발생했습니다.");
    }
}

void SignupWidget::OnCancelClicked()
{
    emit CancelRequested();
}
