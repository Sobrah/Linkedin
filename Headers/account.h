#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>

class Account : public QObject
{
    Q_OBJECT

public:
    explicit Account(QObject * = nullptr);
    ~Account();

    void getInformation();

    // Setters
    void setUsername(const QString &);
    void setPassword(const QByteArray &);
    void setEmail(const QString &);
    void setPhoneNumber(const QString &);
    void setSkill(const QString &);
    void setIsCompany(const bool);

    // Getters
    int getAccountID() const;
    QString getUsername() const;
    QByteArray getPassword() const;
    QString getEmail() const;
    QString getPhoneNumber() const;
    QString getSkill() const;
    bool getIsCompany() const;

protected:
    int accountID = false;
    QString username;
    QByteArray password;
    QString email;
    QString phoneNumber;
    QString skill;
    bool isCompany;
};

#endif // ACCOUNT_H
