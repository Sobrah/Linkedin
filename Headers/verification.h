#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QWidget>

namespace Ui {
class Verification;
}

class Verification : public QWidget
{
    Q_OBJECT

public:
    explicit Verification(bool, QWidget *parent = nullptr);
    ~Verification();

private:
    void confirmButtonClicked();
    void sendEmail(QString, QString);

    Ui::Verification *ui;
    QString code;
    bool formStatus;
};

#endif // VERIFICATION_H
