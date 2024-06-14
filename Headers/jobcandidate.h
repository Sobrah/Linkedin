#ifndef JOBCANDIDATE_H
#define JOBCANDIDATE_H

#include <QWidget>

namespace Ui {
class JobCandidate;
}

class JobCandidate : public QWidget
{
    Q_OBJECT

public:
    explicit JobCandidate(QWidget *parent = nullptr);
    ~JobCandidate();

private:
    void getInformation();

    Ui::JobCandidate *ui;
};

#endif // JOBCANDIDATE_H
