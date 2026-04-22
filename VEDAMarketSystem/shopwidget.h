#ifndef SHOPWIDGET_H
#define SHOPWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include "itemdb.h"

namespace Ui {
class ShopWidget;
}

/**
 * @brief 상품 목록을 표시하고 CRUD 기능을 제공하는 메인 쇼핑 위젯
 *
 * 카테고리 선택, 키워드 검색, 상품 추가 / 수정 / 삭제 기능을 갖추고 있으며
 * 프로필 버튼을 통해 마이페이지 다이얼로그를 열 수 있다.
 */
class ShopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShopWidget(QWidget *parent = nullptr);
    ~ShopWidget();

    /**
     * @brief 현재 로그인한 사용자 이름을 저장한다
     * @param username 로그인된 사용자의 아이디 문자열
     */
    void setUsername(const QString& username);

private slots:
    /**
     * @brief 카테고리 목록에서 항목 클릭 시 호출된다
     *
     * 선택된 카테고리로 currentCategory를 갱신하고,
     * 검색어가 있으면 SearchItems, 없으면 GetItemsByCategory로 목록을 갱신한다.
     *
     * @param item 클릭된 QListWidgetItem 포인터
     */
    void onCategorySelected(QListWidgetItem* item);

    /**
     * @brief 검색창 텍스트 변경 시 호출된다
     *
     * 입력값이 비어 있으면 현재 카테고리 전체 목록을 표시하고,
     * 값이 있으면 currentCategory 범위 내에서 키워드 검색 결과를 표시한다.
     *
     * @param text 변경된 검색어 문자열
     */
    void onSearchTextChanged(const QString& text);

    /**
     * @brief 삭제 버튼 클릭 시 호출된다
     *
     * 선택된 항목이 없으면 경고를 표시하고,
     * 있으면 확인 다이얼로그 후 DB에서 삭제하고 목록을 갱신한다.
     */
    void onDeleteItem();

    /**
     * @brief 추가 버튼 클릭 시 호출된다
     *
     * ItemAddDialog를 열고 Accepted 시 입력된 상품을 DB에 삽입한 뒤 목록을 갱신한다.
     */
    void onAddItem();

    /**
     * @brief 수정 버튼 클릭 시 호출된다
     *
     * 선택된 항목이 없으면 경고를 표시하고,
     * 있으면 ItemModifyDialog를 열어 수정된 내용을 DB에 반영한 뒤 목록을 갱신한다.
     */
    void onModifyItem();

    /**
     * @brief 프로필 버튼 클릭 시 호출된다
     *
     * Mypage 다이얼로그를 열고 로그아웃 / 회원탈퇴 시그널을
     * 상위로 전달하도록 연결한다.
     */
    void onProfileButton();

signals:
    /**
     * @brief 로그아웃 또는 회원 탈퇴가 요청될 때 발생한다
     *
     * Mypage 다이얼로그의 LogoutRequested / AccountDeleted 시그널을
     * 수신하여 상위 위젯으로 전파한다.
     */
    void LogoutRequested();

private:
    /**
     * @brief 전달받은 상품 목록을 ItemCardList 위젯에 카드 형태로 표시한다
     *
     * 기존 목록을 초기화한 뒤 각 Item의 정보를 여러 줄 텍스트로 구성한다.
     *
     * @param items 화면에 표시할 Item 객체 리스트
     */
    void loadCards(const QList<Item>& items);

    Ui::ShopWidget* ui;
    ItemDB db;
    QString currentCategory = "전체";
    QString m_username;
};

#endif // SHOPWIDGET_H