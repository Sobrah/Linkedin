#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

enum Sign
{
    SIGNUP,
    LOGIN
};

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    bool initDatabase();
    void sendEmail(QString, QString);
    inline int fourDigitNumber();
    inline void resetCaptcha();

private slots:
    void on_verificationButton_clicked();
    void on_signButton_clicked();

private:
    Ui::Login *ui;
    Sign signStatus;
};

#endif // LOGIN_H
