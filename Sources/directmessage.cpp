#include <QSqlQuery>
#include <Logics>

DirectMessage::DirectMessage(int accountID)
    : account(new Account)
{
    account->setAccountID(accountID);
    account->selectAccountBaseID();

    qDebug("Direct Message Starts.");
}

DirectMessage::~DirectMessage()
{
    qDebug("Direct Message Ends.");
}

void DirectMessage::insertDirectMessage()
{
    insertContent();

    QSqlQuery query;
    query.prepare("INSERT INTO directMessages (contentID, senderID, receiverID) VALUES (?, ?, ?) "
                  "RETURNING directMessageID");
    query.addBindValue(getContentID());
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(account->getAccountID());
    query.exec();
    query.first();

    // Inserted Direct Message ID
    directMessageID = query.value("directMessageID").toInt();
}

void DirectMessage::selectDirectMessage()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM directMessages WHERE directMessageID = ?");
    query.addBindValue(directMessageID);
    query.exec();

    if (!query.first()) {
        return;
    }

    directMessageID = query.value("directMessageID").toInt();
    setContentID(query.value("contentID").toInt());
    senderID = query.value("senderID").toInt();
    receiverID = query.value("receiverID").toBool();

    selectContent();
}

QVector<int> DirectMessage::selectDirectMessages()
{
    QSqlQuery query;
    query.prepare("SELECT directMessageID FROM directMessages WHERE senderID = ? AND receiverID = "
                  "? ORDER BY directMessageID DESC");
    query.addBindValue(senderID);
    query.addBindValue(receiverID);
    query.exec();

    QVector<int> directMessages;

    while (query.next()) {
        directMessages.append(query.value("directMessageID").toInt());
    }

    return directMessages;
}

void DirectMessage::setDirectMessageID(int directMessageID)
{
    this->directMessageID = directMessageID;
}

void DirectMessage::setSenderID(int senderID)
{
    this->senderID = senderID;
}

void DirectMessage::setReceiverID(int receiverID)
{
    this->receiverID = receiverID;
}

int DirectMessage::getDirectMessageID() const
{
    return directMessageID;
}

int DirectMessage::getSenderID() const
{
    return senderID;
}

int DirectMessage::getReceiverID() const
{
    return receiverID;
}
