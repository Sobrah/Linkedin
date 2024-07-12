#include <QSqlQuery>
#include <QVector>
#include <Logics>

Post::Post(QObject *parent)
    : Content(parent)
{
    qDebug("Post Starts.");
}

Post::~Post()
{
    qDebug("Post Ends.");
}

void Post::insertPost()
{
    insertContent();

    QSqlQuery query;
    query.prepare("INSERT INTO posts (contentID, isReposted) VALUES (?, ?) RETURNING postID");
    query.addBindValue(getContentID());
    query.addBindValue(isReposted);
    query.exec();
    query.first();

    // Inserted Post ID
    postID = query.value("postID").toInt();
}

void Post::selectPost()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM posts WHERE postID = ?");
    query.addBindValue(postID);
    query.exec();

    if (!query.first()) {
        return;
    }

    postID = query.value("postID").toInt();
    setContentID(query.value("contentID").toInt());
    repostCounter = query.value("repostCounter").toInt();
    isReposted = query.value("isReposted").toBool();

    selectContent();
}

QVector<int> Post::selectFeed(int limit, int offset)
{
    QSqlQuery query;
    query.prepare(
        "SELECT postID FROM posts JOIN contents USING(contentID) WHERE NOT senderID = ? "
        "ORDER BY CASE "
        "WHEN senderID IN (SELECT followingID FROM connections WHERE followerID = ?) THEN 1 "
        "WHEN senderID IN (SELECT accountID FROM accounts WHERE skill = ?) THEN 2 "
        "ELSE 3 END, postID DESC LIMIT ? OFFSET ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(ACCOUNT->getAccountID());
    query.addBindValue(ACCOUNT->getSkill());
    query.addBindValue(limit);
    query.addBindValue(offset);
    query.exec();

    // Keep Posts ID
    QVector<int> posts;

    while (query.next()) {
        posts.append(query.value("postID").toInt());
    }

    return posts;
}

void Post::updateRepost()
{
    QSqlQuery query;
    query.prepare("UPDATE posts SET repostCounter = repostCounter + 1 WHERE postID = ?");
    query.addBindValue(postID);
    query.exec();

    repostCounter++;
}

QVector<int> Post::selectAccountPosts(int accountID)
{
    QSqlQuery query;
    query.prepare("SELECT postID FROM posts JOIN contents USING(contentID) "
                  "WHERE senderID = ? ORDER BY postID DESC");
    query.addBindValue(accountID);
    query.exec();

    QVector<int> posts;

    while (query.next()) {
        posts.append(query.value("postID").toInt());
    }

    return posts;
}

void Post::setPostID(int postID)
{
    this->postID = postID;
}

void Post::setRepostCounter(int repostCounter)
{
    this->repostCounter = repostCounter;
}

void Post::setIsReposted(bool isReposted)
{
    this->isReposted = isReposted;
}

int Post::getPostID() const
{
    return postID;
}

int Post::getRepostCounter() const
{
    return repostCounter;
}

bool Post::getIsReposted() const
{
    return isReposted;
}

QVector<Like> Post::getPostLikes() const
{
    return postLikes;
}

QVector<Comment> Post::getPostComments() const
{
    return postComments;
}
