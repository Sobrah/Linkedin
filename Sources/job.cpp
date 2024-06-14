#include <QSqlQuery>
#include <Header>

Job::Job(QObject *parent)
    : QObject(parent)
{
    qDebug("Job Starts.");
}

Job::~Job()
{
    qDebug("Job Ends.");
}

void Job::selectInformation(int number)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM jobs WHERE skill = ? LIMIT 1 OFFSET ?");
    query.addBindValue(ACCOUNT->getSkill());
    query.addBindValue(number);
    query.exec();

    if (!query.first())
        return;

    // Set Information
    jobID = query.value("jobID").toInt();
    companyID = query.value("companyID").toInt();
    title = query.value("title").toString();
    skill = query.value("skill").toString();
    workplaceType = query.value("workplaceType").toString();
    location = query.value("location").toString();
    type = query.value("type").toString();

    // Find Company Name
    query.prepare("SELECT firstName FROM accounts WHERE accountID = ?");
    query.addBindValue(companyID);
    query.exec();
    query.first();

    // Set Company Name
    companyName = query.value("firstName").toString();
}

void Job::insertInformation()
{
    QSqlQuery query;
    query.prepare("INSERT INTO jobs (companyID, title, skill, workplaceType, location, type) "
                  "VALUES (?, ?, ?, ?, ?, ?) RETURNING jobID");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(title);
    query.addBindValue(skill);
    query.addBindValue(workplaceType);
    query.addBindValue(location);
    query.addBindValue(type);
    query.exec();

    if (!query.first()) {
        return;
    }

    // Set Information
    jobID = query.value("jobID").toInt();
}

void Job::selectRequest()
{
    QSqlQuery query;
    query.prepare("SELECT isAccepted FROM jobsRequests WHERE accountID = ? AND jobID = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(jobID);
    query.exec();

    if (!query.first()) {
        isRequested = false;
        isAccepted = false;
        return;
    }

    isRequested = true;
    isAccepted = query.value("isAccepted").toBool();
}

void Job::insertRequest()
{
    if (isRequested) {
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO jobsRequests (accountID, jobID) VALUES (?, ?)");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(jobID);
    query.exec();

    isRequested = true;
}

void Job::deleteRequest()
{
    if (!isRequested) {
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM jobsRequests WHERE accountID = ? AND jobID = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(jobID);
    query.exec();

    isRequested = false;
}

int Job::selectJobsNumber() const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT() FROM jobs WHERE skill = ?");
    query.addBindValue(ACCOUNT->getSkill());
    query.exec();
    query.first();

    return query.value("COUNT()").toInt();
}

void Job::setJobID(int jobID)
{
    this->jobID = jobID;
}

void Job::setCompanyID(int companyID)
{
    this->companyID = companyID;
}

void Job::setTitle(const QString &title)
{
    this->title = title;
}

void Job::setSkill(const QString &skill)
{
    this->skill = skill;
}

void Job::setWorkplaceType(const QString &workplaceType)
{
    this->workplaceType = workplaceType;
}

void Job::setLocation(const QString &location)
{
    this->location = location;
}

void Job::setType(const QString &type)
{
    this->type = type;
}

void Job::setCompanyName(const QString &companyName)
{
    this->companyName = companyName;
}

void Job::setIsRequested(bool isRequested)
{
    this->isRequested = isRequested;
}

void Job::setIsAccepted(bool isAccepted)
{
    this->isAccepted = isAccepted;
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

QString Job::getCompanyName() const
{
    return companyName;
}

bool Job::getIsRequested() const
{
    return isRequested;
}

bool Job::getIsAccepted() const
{
    return isAccepted;
}
