#include "Headers/account.h"

void Account::setAccountId(QString accountId)
{
    this->accountId = accountId;
}

void Account::setPhoneNumber(QString phoneNumber)
{
    this->phoneNumner = phoneNumber;
}

void Account::setEmail(QString email)
{
    this->email = email;
}

void Account::addFollowing(QString following)
{
    this->followings.push_back(following);
}

void Account::addPost(Post post)
{
    this->posts.push_back(post);
}

void Account::addMessage(Direct_Message dm)
{
    this->DM.push_back(dm);
}

QString Account::getAccountId() const
{
    return accountId;
}

QString Account::getPhoneNumber() const
{
    return phoneNumner;
}

QString Account::getEmail() const
{
    return email;
}

QVector<QString> Account::getFollowings() const
{
    return followings;
}

QVector<Post> Account::getPosts() const
{
    return posts;
}

QVector<Direct_Message> Account::getMessages() const
{
    return DM;
}

void Job::setSalary(double salary)
{
    this->salary = salary;
}

void Job::setJobName(QString jobName)
{
    this->jobName = jobName;
}

void Job::setCompanyName(QString companyName)
{
    this->companyName = companyName;
}

void Job::addSkillsRequired(QString skill)
{
    this->skillsRequired.push_back(skill);
}

void Job::setWorkPlaceType(QString workPlaceType)
{
    this->workPlaceType = workPlaceType;
}

void Job::setLocation(QString location)
{
    this->location = location;
}

void Job::setType(QString type)
{
    this->type = type;
}

double Job::getSalary() const
{
    return salary;
}

QString Job::getJobName() const
{
    return jobName;
}

QString Job::getCompanyName() const
{
    return companyName;
}

QVector<QString> Job::getSkillsRequired() const
{
    return skillsRequired;
}

QString Job::getWorkPlaceType() const
{
    return workPlaceType;
}

QString Job::getLocation() const
{
    return location;
}

QString Job::getType() const
{
    return type;
}

void Person::setLastName(QString lastName)
{
    this->lastName = lastName;
}

void Person::setFirstName(QString firstName)
{
    this->firstName = firstName;
}

void Person::addSkill(QString skill)
{
    this->skills.push_back(skill);
}

QString Person::getLastName() const
{
    return lastName;
}

QString Person::getFirstName() const
{
    return firstName;
}

QVector<QString> Person::getSkills() const
{
    return skills;
}

void Company::addJob(Job job)
{
    this->companyJobs.push_back(job);
}

void Company::setCompanyName(QString companyName)
{
    this->companyName = companyName;
}

void Company::addEmployee(Person person)
{
    this->employee.push_back(person);
}

QVector<Job> Company::getCompanyJobs() const
{
    return companyJobs;
}

QString Company::getCompanyName() const
{
    return companyName;
}

QVector<Person> Company::getEmployee() const
{
    return employee;
}
