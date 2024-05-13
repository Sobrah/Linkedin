#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    void verificationButtonClicked();
    void signButtonClicked();
    void sendEmail(QString &, QString &);
    static QString fourRandomDigits();

    Ui::Login *ui;
    bool formStatus = false;

signals:
    void warnMessage(QString, QString);
    void fieldsVerified(QString);
};

#endif // LOGIN_H
