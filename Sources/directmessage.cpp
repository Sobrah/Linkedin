#include "Headers/directmessage.h"

void directMessage::setMessageId(int messageId)
{
    directMessage::messageId = messageId;
}

void directMessage::setToWho(int toWho)
{
    directMessage::toWho = toWho;
}

int directMessage::getMessageId() const
{
    return messageId;
}

int directMessage::getToWho() const
{
    return toWho;
}
