#ifndef USERDB_H
#define USERDB_H

#include "user.h"
#include <QString>

/**
 * @brief users 테이블에 대한 CRUD 접근 클래스.
 *
 * DatabaseManager::Init() 호출 이후 사용해야 한다.
 * 모든 메서드는 "main_connection" 이름의 QSqlDatabase 연결을 사용한다.
 */
class UserDB
{
public:
    UserDB() = default;

    /**
     * @brief 새 사용자를 DB에 추가한다.
     * @param user 추가할 사용자 객체
     * @return 성공 시 true, 실패 시 false
     */
    bool AddUser(const User &user);

    /**
     * @brief 해당 아이디가 이미 존재하는지 확인한다.
     * @param username 확인할 아이디
     * @return 존재하면 true, 없으면 false
     */
    bool UsernameExists(const QString &username);

    /**
     * @brief 아이디와 비밀번호가 일치하는지 확인한다.
     * @param username 확인할 아이디
     * @param password 확인할 비밀번호
     * @return 일치하면 true, 아니면 false
     */
    bool VerifyPassword(const QString &username, const QString &password);

    /**
     * @brief 사용자의 비밀번호를 변경한다.
     * @param username    변경할 사용자 아이디
     * @param newPassword 새 비밀번호
     * @return 성공 시 true, 실패 시 false
     */
    bool UpdatePassword(const QString &username, const QString &newPassword);

    /**
     * @brief 사용자 계정을 DB에서 삭제한다.
     * @param username 삭제할 사용자 아이디
     * @return 성공 시 true, 실패 시 false
     */
    bool DeleteUser(const QString &username);
};

#endif // USERDB_H
