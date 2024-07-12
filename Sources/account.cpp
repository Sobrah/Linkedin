#include <QSqlQuery>
#include <Logics>

Account::Account(QObject *parent)
    : QObject(parent)
{
    qDebug("Account Starts.");
}

Account::~Account()
{
    qDebug("Account Ends.");
}

void Account::selectAccountBaseID()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM accounts WHERE accountID = ?");
    query.addBindValue(accountID);
    query.exec();

    if (!query.first()) {
        return;
    }

    // Update User Information
    setAccount(query);
}

void Account::selectAccountBaseUsername()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM accounts WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);
    query.exec();

    // Invalid Credentials
    if (!query.first())
        return;

    // Update User Information
    setAccount(query);
}

bool Account::selectHasConnection(int followingID)
{
    QSqlQuery query;
    query.prepare("SELECT connectionID FROM connections WHERE followerID = ? AND followingID = ?");
    query.addBindValue(accountID);
    query.addBindValue(followingID);
    query.exec();

    if (query.first()) {
        return true;
    }

    return false;
}

void Account::insertConnection(int followingID)
{
    QSqlQuery query;
    query.prepare("INSERT INTO connections (followerID, followingID) VALUES (?, ?)");
    query.addBindValue(accountID);
    query.addBindValue(followingID);
    query.exec();
}

void Account::deleteConnection(int followingID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM connections WHERE followerID = ? AND followingID = ?");
    query.addBindValue(accountID);
    query.addBindValue(followingID);
    query.exec();
}

QVector<int> Account::selectConnectionRequests()
{
    QSqlQuery query;
    query.prepare("SELECT DISTINCT followerID FROM connectionRequests WHERE followingID = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.exec();

    QVector<int> connectionRequests;

    while (query.next()) {
        connectionRequests.append(query.value("followerID").toInt());
    }

    return connectionRequests;
}

void Account::insertConnectionRequest(int followingID)
{
    QSqlQuery query;
    query.prepare("INSERT INTO connectionRequests (followerID, followingID) VALUES (?, ?)");
    query.addBindValue(accountID);
    query.addBindValue(followingID);
    query.exec();
}

void Account::deleteConnectionRequest(int followingID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM connectionRequests WHERE followerID = ? AND followingID = ?");
    query.addBindValue(accountID);
    query.addBindValue(followingID);
    query.exec();
}

QVector<int> Account::selectConnectionSuggestions(int limit)
{
    QSqlQuery query;
    query.prepare(
        "SELECT accountID FROM accounts "
        "WHERE accountID NOT IN (SELECT followingID FROM connections WHERE followerID = ?) "
        "AND NOT accountID = ? AND isCompany = FALSE ORDER BY CASE "
        "WHEN accountID IN (SELECT followingID FROM connections WHERE followerID IN "
        "(SELECT followingID FROM connections WHERE followerID = ?)) THEN 1 "
        "WHEN skill = ? THEN 2 "
        "ELSE 3 END, accountID DESC LIMIT ?");
    query.addBindValue(accountID);
    query.addBindValue(accountID);
    query.addBindValue(accountID);
    query.addBindValue(skill);
    query.addBindValue(limit);
    query.exec();

    QVector<int> suggestions;

    while (query.next()) {
        suggestions.append(query.value("accountID").toInt());
    }

    return suggestions;
}

int Account::selectAccountIDBaseUsername(QString username)
{
    QSqlQuery query;
    query.prepare("SELECT accountID FROM accounts WHERE username = ?");
    query.addBindValue(username);
    query.exec();
    query.first();

    return query.value("accountID").toInt();
}

QVector<int> Account::selectFollowers()
{
    QSqlQuery query;
    query.prepare("SELECT followerID FROM connections WHERE followingID = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.exec();

    QVector<int> followers;

    while (query.next()) {
        followers.append(query.value("followerID").toInt());
    }

    return followers;
}

void Account::setAccount(const QSqlQuery &query)
{
    accountID = query.value("accountID").toInt();
    username = query.value("username").toString();
    password = query.value("password").toByteArray();
    email = query.value("email").toString();
    phoneNumber = query.value("phoneNumber").toString();
    skill = query.value("skill").toString();
    firstName = query.value("firstName").toString();
    lastName = query.value("lastName").toString();
    isCompany = query.value("isCompany").toBool();
    biography = query.value("biography").toString();
}

void Account::setAccountID(int accountID)
{
    this->accountID = accountID;
}

void Account::setUsername(const QString &username)
{
    this->username = username;
}

void Account::setPassword(const QByteArray &password)
{
    this->password = password;
}

void Account::setEmail(const QString &email)
{
    this->email = email;
}

void Account::setPhoneNumber(const QString &phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

void Account::setSkill(const QString &skill)
{
    this->skill = skill;
}

void Account::setFirstName(const QString &firstName)
{
    this->firstName = firstName;
}

void Account::setLastName(const QString &lastName)
{
    this->lastName = lastName;
}

void Account::setIsCompany(const bool isCompany)
{
    this->isCompany = isCompany;
}

void Account::setBiography(const QString &bio)
{
    this->biography = bio;
}

int Account::getAccountID() const
{
    return accountID;
}

QString Account::getUsername() const
{
    return username;
};

QByteArray Account::getPassword() const
{
    return password;
};

QString Account::getEmail() const
{
    return email;
};

QString Account::getPhoneNumber() const
{
    return phoneNumber;
}

QString Account::getSkill() const
{
    return skill;
}

QString Account::getFirstName() const
{
    return firstName;
}

QString Account::getLastName() const
{
    return lastName;
}

bool Account::getIsCompany() const
{
    return isCompany;
}

QString Account::getBio() const
{
    return biography;
}
