#include "Headers/account.h"

Account::Account(const Account *other)
    : username(other->username)
    , password(other->password)
    , email(other->email)
    , phoneNumber(other->phoneNumber)
    , skill(other->skill)
{}

Account::Account(QString username, QByteArray password, QString email)
    : username(username)
    , password(password)
    , email(email)
{}

void Account::setPhoneNumber(const QString &phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Account::setSkill(const QString &skill)
{
    this->skill = skill;
}

QString Account::getUsername() const
{
    return username;
};

QByteArray Account::getPassword() const
{
    return password;
};

QString Account::getEmail() const
{
    return email;
};

QString Account::getPhoneNumber() const
{
    return phoneNumber;
}

QString Account::getSkill() const
{
    return skill;
}
