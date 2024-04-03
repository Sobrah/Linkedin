#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QNetworkReply>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void sendEmail(QString);

private slots:
    void on_verificationButton_clicked();
    void on_signButton_clicked();
    void checkResponse(QNetworkReply *);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
