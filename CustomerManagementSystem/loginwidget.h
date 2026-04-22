#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class LoginWidget;
}

/**
 * @brief 사용자 로그인 화면 위젯.
 *
 * 아이디/비밀번호 입력 후 로그인 또는 회원가입 화면으로
 * 전환하는 신호를 발생시킨다.
 */
class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief LoginWidget 생성자.
     * @param parent 부모 위젯 (기본값: nullptr)
     */
    explicit LoginWidget(QWidget *parent = nullptr);

    /** @brief 소멸자. 메모리 해제. */
    ~LoginWidget();

signals:
    /**
     * @brief 로그인 버튼 클릭 시 발생하는 신호.
     * @param id       입력된 아이디
     * @param password 입력된 비밀번호
     */
    void LoginRequested(const QString &id, const QString &password);

    /** @brief 회원가입 버튼 클릭 시 발생하는 신호. */
    void SignUpRequested();

private slots:
    /** @brief 로그인 버튼 클릭 슬롯. */
    void OnLoginClicked();

    /** @brief 회원가입 버튼 클릭 슬롯. */
    void OnSignUpClicked();

private:
    Ui::LoginWidget *ui; ///< Qt Designer 생성 UI 포인터
};

#endif // LOGINWIDGET_H
