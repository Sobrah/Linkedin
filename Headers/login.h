#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtConcurrent>

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

private slots:
    void on_signButton_clicked();

private:
    bool initializeDatabase();
    void sendEmail(QString, QString);
    void verificationButtonClicked();
    void handleErrors(QString, QString);
    void resetCaptchaCode();
    static QString fourRandomDigits();

    Ui::Login *ui;
    QThreadPool *pool;
    Sign signStatus;
    QFuture <bool> databaseStatus;

signals:
    void warnMessage(QString, QString);
    void fieldsVerified(QString);
};

#endif // LOGIN_H
