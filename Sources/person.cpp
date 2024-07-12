#include <QSqlError>
#include <QSqlQuery>

#include "Headers/person.h"

Person::Person(const Account *account, QString firstName, QString lastName)
    : firstName(firstName)
    , lastName(lastName)
{
    QSqlQuery query;
    query.prepare("INSERT INTO accounts (username, password, email, phonenumber, skill, firstname, "
                  "lastname, iscompany) VALUES (?, ?, ?, ?, ?, ?, ?, ?) RETURNING accountid");
    query.addBindValue(account->getUsername());
    query.addBindValue(account->getPassword());
    query.addBindValue(account->getEmail());
    query.addBindValue(account->getPhoneNumber());
    query.addBindValue(account->getSkill());
    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(false);
    query.exec();
    query.first();

    accountID = query.value("accountID").toInt();
}

QString Person::getFirstName() const
{
    return firstName;
}

QString Person::getLastName() const
{
    return lastName;
}
