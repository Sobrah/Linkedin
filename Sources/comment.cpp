#include <Logics>

Comment::Comment(QObject *parent)
    : Content(parent)
{
    qDebug("Comment Starts.");
}

Comment::~Comment()
{
    qDebug("Comment Ends.");
}

void Comment::insertComment()
{
    insertContent();

    QSqlQuery query;
    query.prepare("INSERT INTO comments (contentID, postID) VALUES (?, ?) RETURNING commentID");
    query.addBindValue(getContentID());
    query.addBindValue(postID);
    query.exec();
    query.first();

    // Inserted Post ID
    commentID = query.value("commentID").toInt();
}

void Comment::selectComment()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM comments WHERE commentID = ?");
    query.addBindValue(commentID);
    query.exec();

    if (!query.first()) {
        return;
    }

    commentID = query.value("commentID").toInt();
    postID = query.value("postID").toInt();
    setContentID(query.value("contentID").toInt());

    selectContent();
}

QVector<int> Comment::selectComments(int postID)
{
    QSqlQuery query;
    query.prepare("SELECT commentID FROM comments WHERE postID = ? ORDER BY commentID DESC");
    query.addBindValue(postID);
    query.exec();

    QVector<int> comments;

    while (query.next()) {
        comments.append(query.value("commentID").toInt());
    }

    return comments;
}

void Comment::setCommentID(int commentID)
{
    this->commentID = commentID;
}

void Comment::setPostID(int postID)
{
    this->postID = postID;
}

int Comment::getCommentID() const
{
    return commentID;
}

int Comment::getPostID() const
{
    return postID;
}
