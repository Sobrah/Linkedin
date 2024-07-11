#include <QSqlQuery>

#include "Headers/company.h"

Company::Company(const Account *account, QString name)
    : name(name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO accounts (username, password, email, phoneNumber, skill, firstName, "
                  "isCompany) VALUES (?, ?, ?, ?, ?, ?, ?) RETURNING accountID");
    query.addBindValue(account->getUsername());
    query.addBindValue(account->getPassword());
    query.addBindValue(account->getEmail());
    query.addBindValue(account->getPhoneNumber());
    query.addBindValue(account->getSkill());
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
