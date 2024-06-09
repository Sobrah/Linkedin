#include <QSqlQuery>

#include "Headers/person.h"

Person::Person(const Account *account, QString firstName, QString lastName)
    : Account(account)
    , firstName(firstName)
    , lastName(lastName)
{
    QSqlQuery query;
    query.prepare("INSERT INTO accounts (username, password, email, phoneNumber, skill, firstName, "
                  "lastName, isCompany) VALUES (?, ?, ?, ?, ?, ?, ?, ?) RETURNING accountID");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(email);
    query.addBindValue(phoneNumber);
    query.addBindValue(skill);
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
