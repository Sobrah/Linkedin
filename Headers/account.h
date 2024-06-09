#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>

class Account : public QObject
{
    Q_OBJECT
    
public:
    explicit Account(const Account *);
    explicit Account(QString, QByteArray, QString);

    // Setters
    void setPhoneNumber(const QString &);
    void setSkill(const QString &);

    // Getters
    QString getUsername() const;
    QByteArray getPassword() const;
    QString getEmail() const;
    QString getPhoneNumber() const;
    QString getSkill() const;

protected:
    int accountID;
    const QString username;
    const QByteArray password;
    const QString email;
    QString phoneNumber;
    QString skill;
};

#endif // ACCOUNT_H
