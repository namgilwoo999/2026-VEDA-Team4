#include "signupwidget.h"
#include "ui_signupwidget.h"
#include "user.h"
#include <QMessageBox>

SignupWidget::SignupWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignupWidget)
    , m_idChecked(false) {
    ui->setupUi(this);

    // 버튼 클릭 신호 연결
    connect(ui->checkIdButton, SIGNAL(clicked()), this, SLOT(OnCheckIdClicked()));
    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(OnConfirmClicked()));
    connect(ui->cancelButton,  SIGNAL(clicked()), this, SLOT(OnCancelClicked()));

    // 아이디 입력란이 변경되면 중복 확인 플래그 초기화 (확인 우회 방지)
    connect(ui->idLineEdit, &QLineEdit::textChanged, this, [this]() {
        m_idChecked = false;
    });
}

SignupWidget::~SignupWidget() {
    delete ui;
}

void SignupWidget::OnCheckIdClicked() {
    QString id = ui->idLineEdit->text().trimmed();

    // 빈 입력 검사
    if (id.isEmpty()) {
        QMessageBox::warning(this, "알림", "아이디를 입력해주세요.");
        return;
    }

    // DB에서 중복 여부 확인
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

void SignupWidget::OnConfirmClicked() {
    // 아이디 중복 확인 미완료 시 차단
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

    // 필수 입력 항목 검사
    if (id.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "알림", "아이디와 비밀번호는 필수 입력입니다.");
        return;
    }

    User newUser(id, password, name, birth, phone,
                 ui->phoneAlarmCheckBox->isChecked(),
                 email, ui->emailAlarmCheckBox->isChecked());

    // DB 등록 성공 시 폼 전체 초기화 후 신호 발생
    if (m_userDb.AddUser(newUser)) {
        QMessageBox::information(this, "회원가입", "회원가입이 완료되었습니다.");
        ui->idLineEdit->clear();
        ui->passwordLineEdit->clear();
        ui->nameLineEdit->clear();
        ui->phoneLineEdit->clear();
        ui->emailLineEdit->clear();
        m_idChecked = false;
        emit SignupCompleted();
    } else {
        QMessageBox::critical(this, "오류", "회원가입 중 오류가 발생했습니다.");
    }
}

void SignupWidget::OnCancelClicked() {
    emit CancelRequested();
}
