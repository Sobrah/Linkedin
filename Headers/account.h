#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QSqlQuery>

class Account : public QObject
{
    Q_OBJECT

public:
    explicit Account(QObject * = nullptr);
    ~Account();

    void selectAccountBaseID();
    void selectAccountBaseUsername();
    bool selectHasConnection(int);
    void insertConnection(int);
    void deleteConnection(int);

    // Setters
    void setAccountID(int);
    void setUsername(const QString &);
    void setPassword(const QByteArray &);
    void setEmail(const QString &);
    void setPhoneNumber(const QString &);
    void setSkill(const QString &);
    void setIsCompany(const bool);
    void setBio(const QString &);

    // Getters
    int getAccountID() const;
    QString getUsername() const;
    QByteArray getPassword() const;
    QString getEmail() const;
    QString getPhoneNumber() const;
    QString getSkill() const;
    bool getIsCompany() const;
    QString getBio() const;

protected:
    int accountID = false;
    QString username;
    QByteArray password;
    QString email;
    QString phoneNumber;
    QString skill;
    bool isCompany;
    QString bio;

private:
    void setAccount(const QSqlQuery &);
};

#endif // ACCOUNT_H
