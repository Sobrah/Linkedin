#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_verificationButton_clicked();

    void on_signButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
