#ifndef JOBPOSITION_H
#define JOBPOSITION_H

#include <QWidget>

#include "Headers/job.h"

namespace Ui {
class JobPosition;
}

class JobPosition : public QWidget
{
    Q_OBJECT

public:
    explicit JobPosition(int, QWidget *parent = nullptr);
    ~JobPosition();

private:
    void getInformation();
    void statusButtonClicked();

    Ui::JobPosition *ui;
    Job *job;
    int row;
};

#endif // JOBPOSITION_H
