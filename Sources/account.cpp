#include <QSqlQuery>

#include "Headers/account.h"

Account::Account(QString username, QString password, QString email, QString phoneNumber)
    : username(username)
    , password(password)
    , email(email)
    , phoneNumber(phoneNumber)
{
    QSqlQuery query;
    query.prepare("INSERT INTO accounts (username, password, email, phoneNumber) VALUES (?, ?, ?, "
                  "?) RETURNING accountID");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(email);
    query.addBindValue(phoneNumber);
    query.exec();
    query.first();

    // Inserted Account ID
    accountID = query.value("accountID").toInt();
}

int Account::getAccountID() const
{
    return accountID;
};

QString Account::getUsername() const
{
    return username;
};

QString Account::getPassword() const
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
