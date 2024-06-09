#include <QSqlQuery>

#include "Headers/company.h"

Company::Company(const Account *account, QString name)
    : Account(account)
    , name(name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO accounts (username, password, email, phoneNumber, skill, firstName, "
                  "isCompany) VALUES (?, ?, ?, ?, ?, ?, ?) RETURNING accountID");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(email);
    query.addBindValue(phoneNumber);
    query.addBindValue(skill);
    query.addBindValue(name);
    query.addBindValue(true);
    query.exec();
    query.first();

    accountID = query.value("accountID").toInt();
}

QString Company::getName() const
{
    return name;
}
