#ifndef COMMENT_H
#define COMMENT_H

#include "Headers/content.h"

class Comment : private Content
{
private:
    int postId;
    int commentId;

public:
    void setPostId(int);
    void setCommentId(int);
    int getPostId() const;
    int getCommentId() const;
};

#endif // COMMENT_H
