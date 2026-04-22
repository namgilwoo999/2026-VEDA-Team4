# 2026-VEDA-Team4 — Customer Management System

Qt6 기반 판매자 관리 데스크톱 애플리케이션입니다.  
회원가입 / 로그인 / 상품 관리 / 마이페이지 기능을 제공합니다.

---

## 주요 기능

| 기능 | 설명 |
|------|------|
| 회원가입 | 아이디 중복 확인 후 사용자 정보 등록 |
| 로그인 / 로그아웃 | 아이디·비밀번호 인증 후 쇼핑 화면 전환 |
| 상품 조회 | 전체 / 카테고리별 / 키워드 검색 |
| 상품 추가 / 수정 / 삭제 | 이름·카테고리·가격·수량 관리 (동일 상품 재입고 시 수량 합산) |
| 마이페이지 | 비밀번호 변경, 회원탈퇴, 로그아웃 |

---

## 기술 스택

- **언어**: C++17
- **프레임워크**: Qt 6.x (Widgets, Sql)
- **DB**: SQLite (`data/mydatabase.db`)
- **빌드**: CMake 3.16+

---

## 프로젝트 구조

```
CustomerManagementSystem/
├── main.cpp                  # 진입점 — DB 초기화, 시드 로드, 메인 윈도우 실행
├── databasemanager.cpp/h     # SQLite 연결 및 테이블 생성
├── mainwindow.cpp/h/ui       # 화면 전환 컨트롤러 (QStackedWidget)
├── loginwidget.cpp/h/ui      # 로그인 화면
├── signupwidget.cpp/h/ui     # 회원가입 화면
├── shopwidget.cpp/h/ui       # 상품 목록 / 검색 / CRUD 화면
├── itemadddialog.cpp/h/ui    # 상품 추가 다이얼로그
├── itemmodifydialog.cpp/h/ui # 상품 수정 다이얼로그
├── mypage.cpp/h/ui           # 마이페이지 다이얼로그
├── user.cpp/h                # 사용자 도메인 모델
├── userdb.cpp/h              # users 테이블 CRUD
├── item.cpp/h                # 상품 도메인 모델
├── itemdb.cpp/h              # items 테이블 CRUD
├── itemseed.cpp/h            # items.json 초기 데이터 로드
├── items.json                # 초기 상품 시드 데이터
├── style.qss                 # 전역 스타일시트
└── resources.qrc             # 리소스 번들
```

---

## 화면 전환 구조

```
MainWindow (QStackedWidget)
 ├── index 0 : LoginWidget
 ├── index 1 : ShopWidget
 │               └── (dialog) Mypage
 │                               └── signal → ShopWidget → MainWindow
 └── index 2 : SignupWidget
```

---

## 빌드 및 실행

```bash
# Qt Creator에서 열기
File > Open Project > CustomerManagementSystem/CMakeLists.txt

# 또는 커맨드라인
cmake -B build -S CustomerManagementSystem
cmake --build build
```

실행 시 `data/mydatabase.db` 가 자동 생성되며, `items.json` 의 초기 상품 데이터가 로드됩니다.

---

## DB 스키마

```sql
users  (id, username, password, name, birthdate, phone, email, created_at)
items  (id, name, category, price, quantity)
orders (id, user_id, item_id, quantity, created_at)
```

---

## 코딩 스타일

[STYLE.md](./STYLE.md) 참고

- 변수: `camelCase` / 함수·클래스: `PascalCase` / 상수: `UPPER_CASE`
- 중괄호: K&R 스타일
- 헤더 주석: Doxygen (`@brief`, `@param`, `@return`)
- 구현 주석: 함수 내부 로직 단계별 단일 라인 주석
