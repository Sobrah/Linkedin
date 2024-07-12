#ifndef POST_H
#define POST_H

#include "Headers/comment.h"
#include "Headers/content.h"
#include "Headers/like.h"

class Post : public Content
{
public:
    explicit Post(QObject * = nullptr);
    ~Post();

    void insertPost();
    void selectPost();
    QVector<int> selectFeed(int, int);
    void updateRepost();
    QVector<int> selectAccountPosts(int);

    // Setters
    void setPostID(int);
    void setRepostCounter(int);
    void setIsReposted(bool);

    // Getters
    int getPostID() const;
    int getRepostCounter() const;
    bool getIsReposted() const;
    QVector<Like> getPostLikes() const;
    QVector<Comment> getPostComments() const;

private:
    int postID = false;
    int repostCounter = false;
    bool isReposted = false;
    QVector<Like> postLikes;
    QVector<Comment> postComments;
};

#endif // POST_H
