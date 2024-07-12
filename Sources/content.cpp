#include <QSqlQuery>
#include <Logics>

Content::Content(QObject *parent)
    : QObject(parent)
{
    qDebug("Content Starts.");
}

Content::~Content()
{
    qDebug("Content Ends.");
}

void Content::insertContent()
{
    senderID = ACCOUNT->getAccountID();
    timeSent = QDateTime::currentDateTime();

    QSqlQuery query;
    query.prepare("INSERT INTO contents (senderID, timeSent, contentText) "
                  "VALUES (?, ?, ?) RETURNING contentID");
    query.addBindValue(senderID);
    query.addBindValue(timeSent.toString());
    query.addBindValue(contentText);
    query.exec();
    query.first();

    // Inserted Content ID
    contentID = query.value("contentID").toInt();
}

void Content::selectContent()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM contents WHERE contentID = ?");
    query.addBindValue(contentID);
    query.exec();

    if (!query.first()) {
        return;
    }

    senderID = query.value("senderID").toInt();
    timeSent = query.value("timeSent").toDateTime();
    contentText = query.value("contentText").toString();
}

void Content::setContentID(int contentID)
{
    this->contentID = contentID;
}

void Content::setSenderID(int senderID)
{
    this->senderID = senderID;
}

void Content::setTimeSent(const QDateTime &timeSent)
{
    this->timeSent = timeSent;
}

void Content::setContentText(const QString &contentText)
{
    this->contentText = contentText;
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
