#include "Headers/content.h"

void Content::setSenderId(int senderId)
{
    Content::senderId = senderId;
}

void Content::setTimeSent(QDateTime timeSent)
{
    Content::timeSent = timeSent;
}

void Content::setContentText(QString contentText)
{
    Content::contentText = contentText;
}

int Content::getSenderId() const
{
    return senderId;
}

QDateTime Content::getTimeSent() const
{
    return timeSent;
}

QString Content::getContentText() const
{
    return contentText;
}
