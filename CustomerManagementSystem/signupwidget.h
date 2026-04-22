#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>
#include "userdb.h"

namespace Ui {
class SignupWidget;
}

/**
 * @brief 회원가입 화면 위젯.
 *
 * 아이디 중복 확인 후 사용자 정보를 입력받아 DB에 등록한다.
 * 가입 완료 또는 취소 시 신호를 발생시켜 로그인 화면으로 전환한다.
 */
class SignupWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief SignupWidget 생성자.
     * @param parent 부모 위젯 (기본값: nullptr)
     */
    explicit SignupWidget(QWidget *parent = nullptr);

    /** @brief 소멸자. 메모리 해제. */
    ~SignupWidget();

signals:
    /** @brief 회원가입 완료 시 발생하는 신호. */
    void SignupCompleted();

    /** @brief 가입 취소 시 발생하는 신호. */
    void CancelRequested();

private slots:
    /** @brief 가입 확인 버튼 클릭 슬롯. */
    void OnConfirmClicked();

    /** @brief 취소 버튼 클릭 슬롯. */
    void OnCancelClicked();

    /** @brief 아이디 중복 확인 버튼 클릭 슬롯. */
    void OnCheckIdClicked();

private:
    Ui::SignupWidget *ui;          ///< Qt Designer 생성 UI 포인터
    UserDB            m_userDb;    ///< 사용자 DB 접근 객체
    bool              m_idChecked; ///< 아이디 중복 확인 완료 여부
};

#endif // SIGNUPWIDGET_H
