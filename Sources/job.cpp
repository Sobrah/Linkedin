#include <QSqlQuery>

#include "Headers/job.h"
#include "Headers/window.h"

Job::Job(QString title, QString workplaceType, QString location, QString type)
    : companyID(ACCOUNT_ID)
    , title(title)
    , workplaceType(workplaceType)
    , location(location)
    , type(type)
{
    QSqlQuery query;
    query.prepare("INSERT INTO jobs (companyID, title, workplaceType, location, type) VALUES (?, "
                  "?, ?, ?, ?) RETURNING jobID");
    query.addBindValue(companyID);
    query.addBindValue(title);
    query.addBindValue(workplaceType);
    query.addBindValue(location);
    query.addBindValue(type);
    query.exec();
    query.first();

    // Inserted Job ID
    jobID = query.value("jobID").toInt();
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
