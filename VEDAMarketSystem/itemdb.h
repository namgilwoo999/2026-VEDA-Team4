#ifndef ITEMDB_H
#define ITEMDB_H

#include "item.h"
#include <QList>

/**
 * @brief items 테이블에 대한 CRUD 기능을 제공하는 데이터 접근 클래스
 *
 * "main_connection" 으로 열린 SQLite 연결을 사용하며,
 * item 조회 / 검색 / 삽입 / 수정 / 삭제 를 제공한다.
 */
class ItemDB {
public:
    /**
     * @brief 기본 생성자
     */
    ItemDB();

    /**
     * @brief items 테이블의 모든 상품을 반환한다
     * @return 전체 상품 목록, 오류 시 빈 리스트 반환
     */
    QList<Item> GetAllItems();

    /**
     * @brief 특정 카테고리에 속하는 상품 목록을 반환한다
     * @param category 필터링할 카테고리 문자, "전체" 전달 시 모든 상품 반환
     * @return 해당 카테고리의 상품 목록, 오류 시 빈 리스트 반환
     */
    QList<Item> GetItemsByCategory(const QString& category);

    /**
     * @brief 키워드로 상품을 검색한다
     *
     * name 또는 category 컬럼에 keyword가 포함된 상품을 반환한다.
     * category가 "전체"가 아니면 해당 카테고리 내에서만 검색한다.
     *
     * @param keyword  검색할 키워드
     * @param category 검색할 카테고리, 기본값 "전체"
     * @return 검색 결과 상품 목록, 오류 시 빈 리스트 반환
     */
    QList<Item> SearchItems(const QString& keyword, const QString& category = "전체");

    /**
     * @brief id로 단일 상품을 조회한다
     * @param id 조회할 상품의 고유 식별자
     * @return 해당 상품 객체, 존재하지 않거나 오류 시 기본값 Item 반환
     */
    Item GetItemById(int id);

    /**
     * @brief 새 상품을 삽입하거나 기존 상품의 수량을 증가시킨다
     *
     * name과 category가 동일한 상품이 이미 존재하면 quantity를 합산하고,
     * 존재하지 않으면 새 item을 추가한다.
     *
     * @param item 삽입 또는 추가할 Item 객체
     * @return 성공 시 true, 쿼리 실패 시 false
     */
    bool InsertItem(const Item& item);

    /**
     * @brief 기존 상품 정보를 수정한다
     *
     * 기존 item의 name / category / price / quantity를 갱신한다.
     *
     * @param item 수정할 Item 객체
     * @return 성공 시 true, 쿼리 실패 시 false
     */
    bool UpdateItem(const Item& item);

    /**
     * @brief id에 해당하는 상품을 삭제한다
     * @param id 삭제할 상품의 고유 식별자
     * @return 성공 시 true, 쿼리 실패 시 false
     */
    bool DeleteItem(int id);
};

#endif // ITEMDB_H