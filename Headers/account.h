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
    QVector<int> selectConnectionRequests();
    void insertConnectionRequest(int);
    void deleteConnectionRequest(int);
    QVector<int> selectConnectionSuggestions(int);
    int selectAccountIDBaseUsername(QString);
    QVector<int> selectFollowers();

    // Setters
    void setAccountID(int);
    void setUsername(const QString &);
    void setPassword(const QByteArray &);
    void setEmail(const QString &);
    void setPhoneNumber(const QString &);
    void setSkill(const QString &);
    void setFirstName(const QString &);
    void setLastName(const QString &);
    void setIsCompany(const bool);
    void setBiography(const QString &);

    // Getters
    int getAccountID() const;
    QString getUsername() const;
    QByteArray getPassword() const;
    QString getEmail() const;
    QString getPhoneNumber() const;
    QString getSkill() const;
    QString getFirstName() const;
    QString getLastName() const;
    bool getIsCompany() const;
    QString getBiography() const;

protected:
    int accountID = false;
    QString username;
    QByteArray password;
    QString email;
    QString phoneNumber;
    QString skill;
    QString firstName;
    QString lastName;
    bool isCompany;
    QString biography;

private:
    void setAccount(const QSqlQuery &);
};

#endif // ACCOUNT_H
