#ifndef COMMENT_H
#define COMMENT_H

#include "Headers/content.h"

class Comment : public Content
{
public:
    explicit Comment(QObject *parent = nullptr);
    ~Comment();

    void insertComment();
    void selectComment();
    QVector<int> selectComments(int);

    // Setters
    void setCommentID(int);
    void setPostID(int);

    // Getters
    int getCommentID() const;
    int getPostID() const;

private:
    int commentID = false;
    int postID = false;
};

#endif // COMMENT_H
