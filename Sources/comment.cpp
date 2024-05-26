#include "Headers/comment.h"

void Comment::setPostId(int postId)
{
    Comment::postId = postId;
}

void Comment::setCommentId(int commentId)
{
    Comment::commentId = commentId;
}

int Comment::getPostId() const
{
    return postId;
}

int Comment::getCommentId() const
{
    return commentId;
}
