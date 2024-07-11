#ifndef PERSON_H
#define PERSON_H

#include "headers/account.h"

class Person : public Account
{
public:
    Person(const Account *, QString, QString);

    // Getters
    QString getFirstName() const;
    QString getLastName() const;

private:
    QString firstName;
    QString lastName;
};

#endif // PERSON_H
