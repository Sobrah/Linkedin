#ifndef CONTENT_H
#define CONTENT_H

#include <QDateTime>

using namespace std;

class Content
{
private:
    int senderId;
    QDateTime timeSent;
    QString contentText;

public:
    void setSenderId(int);
    void setTimeSent(QDateTime);
    void setContentText(QString);
    int getSenderId() const;
    QDateTime getTimeSent() const;
    QString getContentText() const;
};

#endif // CONTENT_H
