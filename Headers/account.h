#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QVector>
#include "Headers/directmessage.h"
#include "Headers/post.h"

using namespace std;

class Account
{
public:
    void setAccountId(QString);
    void setPhoneNumber(QString);
    void setEmail(QString);
    void addFollowing(QString);
    void addPost(Post);
    void addMessage(directMessage);
    QString getAccountId() const;
    QString getPhoneNumber() const;
    QString getEmail() const;
    QVector<QString> getFollowings() const;
    QVector<Post> getPosts() const;
    QVector<directMessage> getMessages() const;

private:
    QString accountId;
    QString phoneNumner;
    QString email;
    QVector<QString> followings;
    QVector<Post> posts;
    QVector<directMessage> DM;
};

class Job
{
public:
    void setSalary(double);
    void setJobName(QString);
    void setCompanyName(QString);
    void addSkillsRequired(QString);
    void setWorkPlaceType(QString);
    void setLocation(QString);
    void setType(QString);
    double getSalary() const;
    QString getJobName() const;
    QString getCompanyName() const;
    QVector<QString> getSkillsRequired() const;
    QString getWorkPlaceType() const;
    QString getLocation() const;
    QString getType() const;

private:
    double salary;
    QString jobName;
    QString companyName;
    QVector<QString> skillsRequired;
    QString workPlaceType;
    QString location;
    QString type;
};

class Person
{
public:
    void setLastName(QString);
    void setFirstName(QString);
    void addSkill(QString);
    QString getLastName() const;
    QString getFirstName() const;
    QVector<QString> getSkills() const;
    void takeJob(Job);

private:
    QString lastName;
    QString firstName;
    QVector<QString> skills;
};

class Company
{
public:
    void addJob(Job);
    void setCompanyName(QString);
    void addEmployee(Person);
    QVector<Job> getCompanyJobs() const;
    QString getCompanyName() const;
    QVector<Person> getEmployee() const;

private:
    QVector<Job> companyJobs;
    QString companyName;
    QVector<Person> employee;
};

#endif // ACCOUNT_H
