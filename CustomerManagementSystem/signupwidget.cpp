#include "signupwidget.h"
#include "ui_signupwidget.h"

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
    emit CheckIdRequested(ui->idLineEdit->text());
}

void SignupWidget::OnConfirmClicked()
{
    emit SignupRequested(
        ui->idLineEdit->text(),
        ui->passwordLineEdit->text(),
        ui->nameLineEdit->text(),
        ui->birthDateEdit->date().toString("yyyy-MM-dd"),
        ui->phoneLineEdit->text(),
        ui->phoneAlarmCheckBox->isChecked(),
        ui->emailLineEdit->text(),
        ui->emailAlarmCheckBox->isChecked()
    );
}

void SignupWidget::OnCancelClicked()
{
    emit CancelRequested();
}
