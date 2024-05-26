#include "Headers/post.h"

void Post::setPostId(int postId)
{
    Post::postId = postId;
}

void Post::setRepostCounter(int repostCounter)
{
    Post::repostCounter = repostCounter;
}

int Post::getPostId() const
{
    return postId;
}

int Post::getRepostCounter() const
{
    return repostCounter;
}

QVector<Like> Post::getLikes() const
{
    return likes;
}

QVector<Comment> Post::getComments() const
{
    return comments;
}

void Post::addRepostCounter()
{
    repostCounter++;
}
