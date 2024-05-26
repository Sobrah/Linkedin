#ifndef DIRECTMESSAGE_H
#define DIRECTMESSAGE_H

#include "Headers/content.h"

class directMessage : private Content
{
private:
    int messageId;
    int toWho;

public:
    void setMessageId(int);
    void setToWho(int);
    int getMessageId() const;
    int getToWho() const;
};

#endif // DIRECTMESSAGE_H
