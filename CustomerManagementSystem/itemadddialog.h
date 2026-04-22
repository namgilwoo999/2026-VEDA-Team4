#ifndef ITEMADDDIALOG_H
#define ITEMADDDIALOG_H

#include <QDialog>
#include "item.h"

namespace Ui {
class ItemAddDialog;
}

/**
 * @brief 새 상품을 추가하는 다이얼로그 클래스
 *
 * 사용자가 이름 / 카테고리 / 가격 / 수량을 입력하고 추가 버튼을 누르면
 * 입력값을 검증한 뒤 accept()를 호출한다.
 */
class ItemAddDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ItemAddDialog(QWidget *parent = nullptr);
    ~ItemAddDialog();

    /**
     * @brief 현재 UI 입력값으로 구성한 Item 객체를 반환한다
     * @return 입력된 필드가 반영된 Item 객체
     */
    Item getItem() const;

private slots:
    /**
     * @brief 추가 버튼 클릭 시 호출된다
     *
     * 이름 / 가격 / 수량 입력값을 순서대로 검증하고,
     * 모두 통과하면 accept()를 호출하여 다이얼로그를 닫는다.
     * 검증 실패 시 경고 메시지박스를 표시하고 반환한다.
     */
    void onAddButton();

    /**
     * @brief 취소 버튼 클릭 시 호출된다
     *
     * reject()를 호출하여 다이얼로그를 취소 상태로 닫는다.
     */
    void onCancelButton();

private:
    Ui::ItemAddDialog *ui;
};

#endif // ITEMADDDIALOG_H