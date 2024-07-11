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
    bool verificationButtonClicked();
    void signButtonClicked();

    Ui::Login *ui;
    bool formStatus = false;

signals:
    void warnMessage(QString, QString);
};

#endif // LOGIN_H
