#ifndef JOB_H
#define JOB_H

#include <QObject>

class Job : public QObject
{
    Q_OBJECT

public:
    explicit Job(const QString &, int, QObject * = nullptr);
    explicit Job(QString, QString, QString, QString, QString, QObject * = nullptr);

    QString getCompanyName() const;
    bool hasRequested() const;
    bool isAccepted() const;
    void applyRequest() const;
    void removeRequest() const;

    // Getters
    int getJobID() const;
    int getCompanyID() const;
    QString getTitle() const;
    QString getSkill() const;
    QString getWorkplaceType() const;
    QString getLocation() const;
    QString getType() const;

private:
    int jobID = false;
    int companyID;
    QString title;
    QString skill;
    QString workplaceType;
    QString location;
    QString type;
};

#endif // JOB_H
