#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>

/**
 * @brief SQLite 데이터베이스를 관리하는 클래스
 *
 * 데이터베이스 초기화 및 테이블 생성 기능을 제공한다.
 */
class DatabaseManager {

public:
    /**
     * @brief 기본 생성자
     */
    DatabaseManager();

    /**
     * @brief 데이터베이스를 초기화한다
     *
     * data/ 디렉토리를 생성하고 SQLite 데이터베이스 파일에 연결한 뒤
     * 필요한 테이블을 생성한다. 연결 이름은 "main_connection"으로 고정한다.
     *
     * @note 데이터베이스 파일 경로: data/mydatabase.db
     * @return void (연결 실패 시 오류 메시지를 출력하고 반환)
     */
    static void Init();

private:
    /**
     * @brief 테이블을 생성한다
     *
     * users, items 테이블을 생성한다.
     *
     * @return void
     */
    static void CreateTables();
};

#endif // DATABASEMANAGER_H