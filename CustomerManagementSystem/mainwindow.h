#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwidget.h"
#include "shopwidget.h"
#include "signupwidget.h"
#include "userdb.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief 애플리케이션의 메인 윈도우.
 *
 * QStackedWidget을 통해 로그인(0), 쇼핑(1), 회원가입(2) 화면을 전환한다.
 * 각 화면 간 신호를 중계하고 로그인 인증을 담당한다.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow 생성자.
     * @param parent 부모 위젯 (기본값: nullptr)
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /** @brief 소멸자. 메모리 해제. */
    ~MainWindow() override;

private slots:
    /**
     * @brief 로그인 인증을 처리하고 화면을 전환하는 슬롯.
     * @param id       입력된 아이디
     * @param password 입력된 비밀번호
     */
    void OnLoginRequested(const QString &id, const QString &password);

    /** @brief 회원가입 화면(index 2)으로 전환하는 슬롯. */
    void OnSignUpRequested();

    /** @brief 가입 완료 후 로그인 화면(index 0)으로 전환하는 슬롯. */
    void OnSignupCompleted();

    /** @brief 회원가입 취소 시 로그인 화면(index 0)으로 전환하는 슬롯. */
    void OnSignUpCancelled();

    /** @brief 로그아웃 시 로그인 화면(index 0)으로 전환하는 슬롯. */
    void OnLogoutRequested();

private:
    Ui::MainWindow *ui;            ///< Qt Designer 생성 UI 포인터
    LoginWidget    *m_loginWidget;  ///< 로그인 화면 위젯
    ShopWidget     *m_shopWidget;   ///< 쇼핑 화면 위젯
    SignupWidget   *m_signupWidget; ///< 회원가입 화면 위젯
    UserDB          m_userDb;       ///< 사용자 DB 접근 객체
};

#endif // MAINWINDOW_H
