#ifndef LOGIN_H
#define LOGIN_H

#include <QThreadPool>
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
    bool initializeDatabase();
    void sendEmail(QString &, QString &);
    static QString fourRandomDigits();

    Ui::Login *ui;
    QThreadPool *pool;
    bool databaseStatus = false;
    bool formLoginStatus = false;

signals:
    void warnMessage(QString, QString);
    void fieldsVerified(QString);
};

#endif // LOGIN_H
