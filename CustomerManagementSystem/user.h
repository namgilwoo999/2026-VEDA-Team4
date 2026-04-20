#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

class User
{
public:
    User(const QString &id, const QString &password,
         const QString &name, const QDate &birth,
         const QString &phone, bool phoneAlarm,
         const QString &email, bool emailAlarm);

    QString GetId()       const;
    QString GetPassword() const;
    QString GetName()     const;
    QDate   GetBirth()    const;
    QString GetPhone()    const;
    bool    GetPhoneAlarm() const;
    QString GetEmail()    const;
    bool    GetEmailAlarm() const;

    void SetPassword(const QString &password);
    void SetPhone(const QString &phone);
    void SetPhoneAlarm(bool alarm);
    void SetEmail(const QString &email);
    void SetEmailAlarm(bool alarm);

private:
    QString m_id;
    QString m_password;
    QString m_name;
    QDate   m_birth;
    QString m_phone;
    bool    m_phoneAlarm;
    QString m_email;
    bool    m_emailAlarm;
};

#endif // USER_H
