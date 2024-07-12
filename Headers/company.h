#ifndef COMPANY_H
#define COMPANY_H

#include "Headers/account.h"
#include "Headers/job.h"
#include "Headers/person.h"

class Company : public Account
{
public:
    Company(const Account *, QString);

    // Getters
    QString getName() const;
    QVector<Job> getCompanyJobs() const;
    QVector<Person> getCompanyEmployees() const;
    QVector<Person> getCompanyFollowings() const;

private:
    QString name;
    QVector<Job> companyJobs;
    QVector<Person> companyEmployees;
    QVector<Person> companyFollowings;
};

#endif // COMPANY_H
