#ifndef MYPAGE_H
#define MYPAGE_H

#include <QDialog>
#include "userdb.h"

namespace Ui {
class Mypage;
}

/**
 * @brief 사용자 마이페이지 다이얼로그.
 *
 * 비밀번호 변경, 회원탈퇴, 로그아웃 기능을 제공한다.
 * 메뉴 목록 선택에 따라 내부 스택 위젯이 전환된다.
 */
class Mypage : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Mypage 생성자.
     * @param username 현재 로그인한 사용자의 아이디
     * @param parent   부모 위젯 (기본값: nullptr)
     */
    explicit Mypage(const QString &username, QWidget *parent = nullptr);

    /** @brief 소멸자. 메모리 해제. */
    ~Mypage();

signals:
    /** @brief 회원탈퇴 완료 시 발생하는 신호. */
    void AccountDeleted();

    /** @brief 로그아웃 요청 시 발생하는 신호. */
    void LogoutRequested();

private slots:
    /**
     * @brief 메뉴 항목 선택 시 해당 페이지로 전환하는 슬롯.
     * @param row 선택된 행 인덱스
     */
    void OnMenuItemClicked(int row);

    /** @brief 비밀번호 변경 버튼 클릭 슬롯. */
    void OnChangePasswordClicked();

    /** @brief 회원탈퇴 확인 버튼 클릭 슬롯. */
    void OnConfirmDeleteClicked();

    /** @brief 비밀번호 변경 취소 버튼 클릭 슬롯. */
    void OnCancelPasswordClicked();

    /** @brief 회원탈퇴 취소 버튼 클릭 슬롯. */
    void OnCancelDeleteClicked();

    /** @brief 로그아웃 버튼 클릭 슬롯. */
    void OnLogoutClicked();

private:
    Ui::Mypage *ui;      ///< Qt Designer 생성 UI 포인터
    UserDB      m_userDb;    ///< 사용자 DB 접근 객체
    QString     m_username;  ///< 현재 로그인한 사용자 아이디
};

#endif // MYPAGE_H
