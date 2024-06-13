#include <QSqlQuery>

#include "Headers/job.h"
#include "Headers/utility.h"

Job::Job(const QString &skill, int row, QObject *parent)
    : QObject(parent)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM jobs WHERE skill = ? LIMIT 1 OFFSET ?");
    query.addBindValue(skill);
    query.addBindValue(row);
    query.exec();

    if (!query.first())
        return;

    jobID = query.value("jobID").toInt();
    companyID = query.value("companyID").toInt();
    title = query.value("title").toString();
    workplaceType = query.value("workplaceType").toString();
    location = query.value("location").toString();
    type = query.value("type").toString();
}

Job::Job(QString title,
         QString skill,
         QString workplaceType,
         QString location,
         QString type,
         QObject *parent)
    : QObject(parent)
    , companyID(ACCOUNT->getAccountID())
    , title(title)
    , skill(skill)
    , workplaceType(workplaceType)
    , location(location)
    , type(type)
{
    QSqlQuery query;
    query.prepare(
        "INSERT INTO jobs (companyID, title, skill, workplaceType, location, type) VALUES (?, "
        "?, ?, ?, ?, ?) RETURNING jobID");
    query.addBindValue(companyID);
    query.addBindValue(title);
    query.addBindValue(skill);
    query.addBindValue(workplaceType);
    query.addBindValue(location);
    query.addBindValue(type);
    query.exec();
    query.first();

    // Inserted Job ID
    jobID = query.value("jobID").toInt();
}

QString Job::getCompanyName() const
{
    QSqlQuery query;
    query.prepare("SELECT firstName FROM accounts WHERE accountID = ?");
    query.addBindValue(companyID);
    query.exec();

    if (!query.first())
        return QString();

    return query.value("firstName").toString();
}

bool Job::hasRequested() const
{
    QSqlQuery query;
    query.prepare("SELECT jobsRequestsID FROM jobsRequests WHERE accountID = ? AND jobID = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(jobID);
    query.exec();

    if (query.first()) {
        return true;
    }

    return false;
}

bool Job::isAccepted() const
{
    QSqlQuery query;
    query.prepare("SELECT isAccepted FROM jobsRequests WHERE accountID = ? AND job = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(jobID);
    query.exec();

    if (!query.first())
        return false;

    if (query.value("isAccepted").toBool())
        return true;

    return false;
}

void Job::applyRequest() const
{
    QSqlQuery query;
    query.prepare("INSERT INTO jobsRequests (accountID, jobID) VALUES (?, ?)");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(jobID);
    query.exec();
}

void Job::removeRequest() const
{
    QSqlQuery query;
    query.prepare("DELETE FROM jobsRequests WHERE accountID = ? AND jobID = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(jobID);
    query.exec();
}

int Job::getJobID() const
{
    return jobID;
}

int Job::getCompanyID() const
{
    return companyID;
}

QString Job::getTitle() const
{
    return title;
}

QString Job::getWorkplaceType() const
{
    return workplaceType;
}

QString Job::getLocation() const
{
    return location;
}

QString Job::getType() const
{
    return type;
}
