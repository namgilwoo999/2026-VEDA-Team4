#ifndef ITEM_H
#define ITEM_H
#include <QString>

/**
 * @brief 상품 정보를 담는 데이터 클래스
 *
 * id / name / category / price / quantity 필드를 관리한다.
 */
class Item {
private:
    int id;
    QString name;
    QString category;
    int price;
    int quantity;

public:
    /**
     * @brief 기본 생성자
     * @note id, price, quantity는 0으로 초기화되고 문자열 필드는 빈 값으로 초기화된다
     */
    Item();
    /**
     * @brief 모든 필드를 지정하는 생성자
     * @param id       상품 고유 식별자
     * @param name     상품명
     * @param category 상품 카테고리
     * @param price    상품 가격
     * @param quantity 재고 수량
     */
    Item(int id, QString name, QString category, int price, int quantity);

    /**
     * @brief 상품 고유 식별자를 반환한다
     * @return 상품 id
     */
    int GetId() const;

    /**
     * @brief 상품명을 반환한다
     * @return 상품명 문자열
     */
    QString GetName() const;

    /**
     * @brief 상품 카테고리를 반환한다
     * @return 카테고리 문자열
     */
    QString GetCategory() const;

    /**
     * @brief 상품 가격을 반환한다
     * @return 가격 (정수)
     */
    int GetPrice() const;

    /**
     * @brief 재고 수량을 반환한다
     * @return 재고 수량 (정수)
     */
    int GetQuantity() const;

    /**
     * @brief 상품 고유 식별자를 설정한다
     * @param id 설정할 상품 id
     */
    void SetId(int id);

    /**
     * @brief 상품명을 설정한다
     * @param name 설정할 상품명
     */
    void SetName(QString name);

    /**
     * @brief 상품 카테고리를 설정한다
     * @param category 설정할 카테고리 문자열
     */
    void SetCategory(QString category);

    /**
     * @brief 상품 가격을 설정한다
     * @param price 설정할 가격 (정수)
     */
    void SetPrice(int price);

    /**
     * @brief 재고 수량을 설정한다
     * @param quantity 설정할 재고 수량 (정수)
     */
    void SetQuantity(int quantity);
};

#endif // ITEM_H