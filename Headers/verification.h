#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QWidget>

#include "Headers/account.h"

namespace Ui {
class Verification;
}

class Verification : public QWidget
{
    Q_OBJECT

public:
    explicit Verification(Account *, bool, QWidget *parent = nullptr);
    ~Verification();

private:
    void confirmButtonClicked();
    void sendEmail(QString, QString);

    Ui::Verification *ui;
    Account *account;
    QString code;
    bool formStatus;
};

#endif // VERIFICATION_H
