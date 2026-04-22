#ifndef ITEMSEED_H
#define ITEMSEED_H

class ItemDB;

/**
 * @brief items 테이블에 초기 데이터를 삽입하는 시드 클래스
 *
 * Qt 리소스에 포함된 JSON 파일을 읽어 ItemDB를 통해
 * 초기 상품 데이터를 DB에 추가한다.
 */
class ItemSeed
{
public:
    /**
     * @brief JSON 파일을 읽어 상품 초기 데이터를 DB에 삽입한다
     *
     * Qt 리소스 경로(:/items.json)에서 JSON 배열을 읽고,
     * 각 객체를 Item으로 변환하여 삽입한다.
     *
     * @param db 데이터를 삽입할 ItemDB 객체
     * @return void (파일 열기 실패 또는 JSON 형식 오류 시 조기 반환)
     */
    static void load(ItemDB& db);
};

#endif // ITEMSEED_H