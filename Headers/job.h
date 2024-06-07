#ifndef JOB_H
#define JOB_H

#include <QObject>

class Job : public QObject
{
    Q_OBJECT

public:
    explicit Job(QString, QString, QString, QString);

    // Getters
    int getJobID() const;
    int getCompanyID() const;
    QString getTitle() const;
    QString getWorkplaceType() const;
    QString getLocation() const;
    QString getType() const;

private:
    int jobID;
    const int companyID;
    QString title;
    QString workplaceType;
    QString location;
    QString type;
};

#endif // JOB_H
