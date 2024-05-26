#ifndef CONTENT_H
#define CONTENT_H

#include <QDateTime>
#include <QObject>

class Content : public QObject
{
    Q_OBJECT

public:
    explicit Content(const QString &);

    // Setters
    void setTimeSent(const QDateTime &);
    void setContentText(const QString &);

    // Getters
    int getContentID() const;
    int getSenderID() const;
    QDateTime getTimeSent() const;
    QString getContentText() const;

private:
    int contentID;
    const int senderID;
    QDateTime timeSent;
    QString contentText;
};

#endif // CONTENT_H
