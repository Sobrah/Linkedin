#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

#include "Headers/account.h"

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(Account *, QWidget *parent = nullptr);
    ~Profile();

private:
    void submitButtonClicked();
    void companyButtonClicked();

    Ui::Profile *ui;
    Account *account;
    bool formStatus = false;

signals:
    void warnMessage(QString, QString);
};

#endif // PROFILE_H
