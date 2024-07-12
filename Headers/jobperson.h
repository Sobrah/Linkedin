#ifndef JOBPERSON_H
#define JOBPERSON_H

#include <QWidget>

namespace Ui {
class JobPerson;
}

class JobPerson : public QWidget
{
    Q_OBJECT

public:
    explicit JobPerson(QWidget *parent = nullptr);
    ~JobPerson();

private:
    Ui::JobPerson *ui;
    int offset = false;
    int jobsNumber = false;
};

#endif // JOBPERSON_H
