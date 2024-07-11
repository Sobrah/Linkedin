#ifndef JOBCANDIDATE_H
#define JOBCANDIDATE_H

#include <QWidget>
#include "Headers/account.h"
#include "Headers/job.h"

namespace Ui {
class JobCandidate;
}

class JobCandidate : public QWidget
{
    Q_OBJECT

public:
    explicit JobCandidate(int, QWidget *parent = nullptr);
    ~JobCandidate();

private:
    void acceptButtonClicked();
    void rejectButtonClicked();

    Ui::JobCandidate *ui;
    Account *account;
    Job *job;
    int jobRequestID;
};

#endif // JOBCANDIDATE_H
