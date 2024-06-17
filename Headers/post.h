#ifndef POST_H
#define POST_H

#include "Headers/content.h"

class Post : public Content
{
public:
    explicit Post(QObject * = nullptr);
    ~Post();

    void insertPost();
    void selectPost();
    QVector<int> selectFeed(int limit, int offset);

    // Setters
    void setPostID(int);

    // Getters
    int getPostID() const;

private:
    int postID = false;
};

#endif // POST_H
