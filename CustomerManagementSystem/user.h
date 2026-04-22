#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

/**
 * @brief 사용자 정보를 담는 도메인 모델 클래스.
 *
 * 아이디, 비밀번호, 이름, 생년월일, 연락처, 알림 설정, 이메일 등
 * 사용자 계정에 관련된 모든 정보를 보유한다.
 */
class User {
public:
    /**
     * @brief User 생성자.
     * @param id         사용자 아이디 (고유 식별자)
     * @param password   비밀번호
     * @param name       실명
     * @param birth      생년월일
     * @param phone      전화번호
     * @param phoneAlarm 전화 알림 수신 여부
     * @param email      이메일 주소
     * @param emailAlarm 이메일 알림 수신 여부
     */
    User(const QString &id, const QString &password,
         const QString &name, const QDate &birth,
         const QString &phone, bool phoneAlarm,
         const QString &email, bool emailAlarm);

    /** @brief 사용자 아이디를 반환한다. */
    QString GetId()         const;

    /** @brief 비밀번호를 반환한다. */
    QString GetPassword()   const;

    /** @brief 실명을 반환한다. */
    QString GetName()       const;

    /** @brief 생년월일을 반환한다. */
    QDate   GetBirth()      const;

    /** @brief 전화번호를 반환한다. */
    QString GetPhone()      const;

    /** @brief 전화 알림 수신 여부를 반환한다. */
    bool    GetPhoneAlarm() const;

    /** @brief 이메일 주소를 반환한다. */
    QString GetEmail()      const;

    /** @brief 이메일 알림 수신 여부를 반환한다. */
    bool    GetEmailAlarm() const;

    /**
     * @brief 비밀번호를 변경한다.
     * @param password 새 비밀번호
     */
    void SetPassword(const QString &password);

    /**
     * @brief 전화번호를 변경한다.
     * @param phone 새 전화번호
     */
    void SetPhone(const QString &phone);

    /**
     * @brief 전화 알림 수신 여부를 설정한다.
     * @param alarm true면 알림 활성화
     */
    void SetPhoneAlarm(bool alarm);

    /**
     * @brief 이메일 주소를 변경한다.
     * @param email 새 이메일 주소
     */
    void SetEmail(const QString &email);

    /**
     * @brief 이메일 알림 수신 여부를 설정한다.
     * @param alarm true면 알림 활성화
     */
    void SetEmailAlarm(bool alarm);

private:
    QString m_id;         ///< 사용자 아이디
    QString m_password;   ///< 비밀번호
    QString m_name;       ///< 실명
    QDate   m_birth;      ///< 생년월일
    QString m_phone;      ///< 전화번호
    bool    m_phoneAlarm; ///< 전화 알림 수신 여부
    QString m_email;      ///< 이메일 주소
    bool    m_emailAlarm; ///< 이메일 알림 수신 여부
};

#endif // USER_H
