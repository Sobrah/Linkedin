#ifndef CONTENT_H
#define CONTENT_H

#include <QDateTime>
#include <QObject>

class Content : public QObject
{
    Q_OBJECT

public:
    explicit Content(QObject * = nullptr);
    ~Content();

    void insertContent();
    void selectContent();

    // Setters
    void setContentID(int);
    void setSenderID(int);
    void setTimeSent(const QDateTime &);
    void setContentText(const QString &);

    // Getters
    int getContentID() const;
    int getSenderID() const;
    QDateTime getTimeSent() const;
    QString getContentText() const;

private:
    int contentID = false;
    int senderID = false;
    QDateTime timeSent;
    QString contentText;
};

#endif // CONTENT_H
