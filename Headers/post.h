#ifndef POST_H
#define POST_H

#include "Headers/comment.h"
#include "Headers/content.h"
#include "Headers/like.h"

class Post : private Content
{
private:
    int postId;
    int repostCounter;
    QVector<Like> likes;
    QVector<Comment> comments;

public:
    void setPostId(int);
    void setRepostCounter(int);
    int getPostId() const;
    int getRepostCounter() const;
    QVector<Like> getLikes() const;
    QVector<Comment> getComments() const;
    void addRepostCounter();
};

#endif // POST_H
