#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H

#include <QObject>
#include <QSqlQuery>
#include "Headers/account.h"
#include "Headers/content.h"

class DirectMessage : public Content
{
public:
    explicit DirectMessage(int);
    ~DirectMessage();

    void insertDirectMessage();
    void selectDirectMessage();
    QVector<int> selectDirectMessages();

    // Setters
    void setDirectMessageID(int);
    void setSenderID(int);
    void setReceiverID(int);

    // Getters
    int getDirectMessageID() const;
    int getSenderID() const;
    int getReceiverID() const;

private:
    Account *account;
    int directMessageID = false;
    int senderID = false;
    int receiverID = false;
};

#endif // DIRECTMESSAGE_H
