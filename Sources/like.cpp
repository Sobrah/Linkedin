#include <QSqlQuery>
#include <Logics>

Like::Like(QObject *parent)
    : QObject(parent)
{
    qDebug("Like Starts.");
}

Like::~Like()
{
    qDebug("Like Ends.");
}

void Like::deleteLike(int postID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM likes WHERE whoLikedID = ? AND postID = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(postID);
    query.exec();
}

void Like::insertLike(int postID)
{
    QSqlQuery query;
    query.prepare("INSERT INTO likes (whoLikedID, postID) VALUES (?, ?)");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(postID);
    query.exec();
}

bool Like::selectHasLike(int postID)
{
    QSqlQuery query;
    query.prepare("SELECT likeID FROM likes WHERE whoLikedID = ? AND postID = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(postID);
    query.exec();

    if (query.first()) {
        return true;
    }

    return false;
}

QVector<int> Like::selectLikesBasePost(int postID)
{
    QSqlQuery query;
    query.prepare("SELECT whoLikedID FROM likes WHERE postID = ?");
    query.addBindValue(postID);
    query.exec();

    QVector<int> accounts;

    while (query.next()) {
        accounts.append(query.value("whoLikedID").toInt());
    }

    return accounts;
}

int Like::selectCountPostLikes(int postID)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM likes WHERE postID = ?");
    query.addBindValue(postID);
    query.exec();
    query.first();

    return query.value("COUNT").toInt();
}

void Like::setLikeID(int likeID)
{
    this->likeID = likeID;
}

void Like::setWhoLikedID(int whoLikedID)
{
    this->whoLikedID = whoLikedID;
}

void Like::setPostID(int postID)
{
    this->postID = postID;
}

int Like::getLikeID() const
{
    return likeID;
}

int Like::getWhoLikedID() const
{
    return whoLikedID;
}

int Like::getPostID() const
{
    return postID;
}
