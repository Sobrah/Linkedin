#ifndef COMPANY_H
#define COMPANY_H

#include "Headers/account.h"

class Company : public Account
{
public:
    Company(const Account *, QString);

    // Getters
    QString getName() const;

private:
    QString name;
};

#endif // COMPANY_H
