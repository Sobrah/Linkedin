#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>

class Account : public QObject
{
    Q_OBJECT
    
public:
    explicit Account(QString, QString, QString, QString);

    // Getters
    int getAccountID() const;
    QString getUsername() const;
    QString getPassword() const;
    QString getEmail() const;
    QString getPhoneNumber() const;

private:
    int accountID;
    const QString username;
    const QString password;
    const QString email;
    const QString phoneNumber;
};

#endif // ACCOUNT_H
