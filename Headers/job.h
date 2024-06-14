#ifndef JOB_H
#define JOB_H

#include <QObject>

class Job : public QObject
{
    Q_OBJECT

public:
    explicit Job(QObject * = nullptr);
    ~Job();

    // Database
    void insertInformation();
    void selectInformation(int);
    void selectRequest();
    void insertRequest();
    void deleteRequest();
    int selectJobsNumber() const;

    // Setters
    void setJobID(int);
    void setCompanyID(int);
    void setTitle(const QString &);
    void setSkill(const QString &);
    void setWorkplaceType(const QString &);
    void setLocation(const QString &);
    void setType(const QString &);
    void setCompanyName(const QString &);
    void setIsRequested(bool);
    void setIsAccepted(bool);

    // Getters
    int getJobID() const;
    int getCompanyID() const;
    QString getTitle() const;
    QString getSkill() const;
    QString getWorkplaceType() const;
    QString getLocation() const;
    QString getType() const;
    QString getCompanyName() const;
    bool getIsRequested() const;
    bool getIsAccepted() const;

private:
    int jobID = false;
    int companyID = false;
    QString title;
    QString skill;
    QString workplaceType;
    QString location;
    QString type;

    QString companyName;
    bool isRequested = false;
    bool isAccepted = false;
};

#endif // JOB_H
