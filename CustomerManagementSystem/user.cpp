#include "user.h"

User::User(const QString &id, const QString &password,
           const QString &name, const QDate &birth,
           const QString &phone, bool phoneAlarm,
           const QString &email, bool emailAlarm)
    : m_id(id)
    , m_password(password)
    , m_name(name)
    , m_birth(birth)
    , m_phone(phone)
    , m_phoneAlarm(phoneAlarm)
    , m_email(email)
    , m_emailAlarm(emailAlarm)
{

}

QString User::GetId() const {
    return m_id;
}

QString User::GetPassword() const {
    return m_password;
}

QString User::GetName() const {
    return m_name;
}

QDate User::GetBirth() const {
    return m_birth;
}

QString User::GetPhone() const {
    return m_phone;
}

bool User::GetPhoneAlarm() const {
    return m_phoneAlarm;
}

QString User::GetEmail() const {
    return m_email;
}

bool User::GetEmailAlarm() const {
    return m_emailAlarm;
}

void User::SetPassword(const QString &password) {
    m_password = password;
}

void User::SetPhone(const QString &phone) {
    m_phone = phone;
}

void User::SetPhoneAlarm(bool alarm) {
    m_phoneAlarm = alarm;
}

void User::SetEmail(const QString &email) {
    m_email = email;
}

void User::SetEmailAlarm(bool alarm) {
    m_emailAlarm = alarm;
}
