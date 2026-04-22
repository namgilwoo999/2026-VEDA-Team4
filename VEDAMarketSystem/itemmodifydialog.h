#ifndef ITEMMODIFYDIALOG_H
#define ITEMMODIFYDIALOG_H

#include <QDialog>
#include "item.h"

namespace Ui {
class ItemModifyDialog;
}

/**
 * @brief 기존 상품 정보를 수정하는 다이얼로그 클래스
 *
 * 호출 시 전달받은 Item 객체의 값을 UI에 미리 채워 보여주고,
 * 사용자가 수정 후 확인하면 입력값을 검증한 뒤 accept()를 호출한다.
 */
class ItemModifyDialog : public QDialog {
    Q_OBJECT
public:
    explicit ItemModifyDialog(const Item& item, QWidget *parent = nullptr);
    ~ItemModifyDialog();

    /**
     * @brief 현재 UI 입력값으로 구성한 Item 객체를 반환한다
     * @return 수정된 필드가 반영된 Item 객체
     */
    Item getItem() const;

private slots:
    /**
     * @brief 수정 버튼 클릭 시 호출된다
     *
     * 이름 / 가격 / 수량 입력값을 순서대로 검증하고,
     * 모두 통과하면 accept()를 호출하여 다이얼로그를 닫는다.
     * 검증 실패 시 경고 메시지박스를 표시하고 반환한다.
     */
    void onModifyButton();

    /**
     * @brief 취소 버튼 클릭 시 호출된다
     *
     * reject()를 호출하여 다이얼로그를 취소 상태로 닫는다.
     */
    void onCancelButton();

private:
    Ui::ItemModifyDialog *ui;
};

#endif // ITEMMODIFYDIALOG_H