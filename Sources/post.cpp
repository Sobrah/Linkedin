#include <QSqlQuery>

#include "Headers/post.h"

Post::Post(const QString &contentText)
    : Content(contentText)
{
    QSqlQuery query;
    query.prepare("INSERT INTO posts (contentID) VALUES (?) RETURNING postID");
    query.addBindValue(getContentID());
    query.exec();
    query.first();

    // Inserted Post ID
    postID = query.value("postID").toInt();
}

int Post::getPostID() const
{
    return postID;
}
