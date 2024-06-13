#include <QSqlQuery>

#include "Headers/content.h"
#include "Headers/utility.h"

Content::Content(const QString &contentText)
    : senderID(ACCOUNT->getAccountID())
    , timeSent(QDateTime::currentDateTime())
    , contentText(contentText)
{
    QSqlQuery query;
    query.prepare("INSERT INTO contents (senderID, timeSent, contentText) VALUES (?, ?, ?) "
                  "RETURNING contentID");
    query.addBindValue(senderID);
    query.addBindValue(timeSent.toString());
    query.addBindValue(contentText);
    query.exec();
    query.first();

    // Inserted Content ID
    contentID = query.value("contentID").toInt();
}

void Content::setTimeSent(const QDateTime &timeSent)
{
    Content::timeSent = timeSent;
}

void Content::setContentText(const QString &contentText)
{
    Content::contentText = contentText;
}

int Content::getContentID() const
{
    return contentID;
}

int Content::getSenderID() const
{
    return senderID;
}

QDateTime Content::getTimeSent() const
{
    return timeSent;
}

QString Content::getContentText() const
{
    return contentText;
}
