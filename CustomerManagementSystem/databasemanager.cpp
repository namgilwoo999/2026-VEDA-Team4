#include "databasemanager.h"
#include <QDir>

DatabaseManager::DatabaseManager() {}

void DatabaseManager::Init() {
    // 디렉토리 생성 및 데이터베이스 연결
    QDir().mkpath("data");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","main_connection");
    db.setDatabaseName("data/mydatabase.db");
    if (!db.open()) {
        qDebug() << "DB Open Error:" << db.lastError().text();
        return;
    }

    // 테이블 생성
    CreateTables();
}

void DatabaseManager::CreateTables() {
    QSqlQuery query(QSqlDatabase::database("main_connection"));

    // users 테이블 생성
    // - id       : 기본키
    // - username : 로그인에 사용할 아이디
    // - password : 비밀번호
    // - name     : 사용자 이름
    // - birthdate: 생년월일
    // - phone    : 연락처
    // - email    : 이메일
    // - created_at: 계정 생성 시각
    query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL, "
        "password TEXT NOT NULL, "
        "name TEXT, "
        "birthdate DATE, "
        "phone TEXT, "
        "email TEXT, "
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
        ")"
        );

    // items 테이블 생성
    // - id        : 기본키
    // - name      : 상품명
    // - category  : 상품 카테고리
    // - price     : 가격
    // - quantity  : 재고 수량
    query.exec(
        "CREATE TABLE IF NOT EXISTS items ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "category TEXT, "
        "price INTEGER, "
        "quantity INTEGER"
        ")"
        );
}