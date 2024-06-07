#ifndef JOBCOMPANY_H
#define JOBCOMPANY_H

#include <QWidget>

namespace Ui {
class JobCompany;
}

class JobCompany : public QWidget
{
    Q_OBJECT

public:
    explicit JobCompany(QWidget *parent = nullptr);
    ~JobCompany();

private:
    void createJobButtonClicked();

    Ui::JobCompany *ui;
};

#endif // JOBCOMPANY_H
