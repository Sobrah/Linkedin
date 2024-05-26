#ifndef LIKE_H
#define LIKE_H

#include <QDateTime>

class Like
{
private:
    int whoLikedId;
    int likeId;
    QDateTime whenLiked;

public:
    void setWhoLikedId(int);
    void setLikeId(int);
    void setWhenLiked(QDateTime);
    int getWhoLikedId() const;
    int getLikeId() const;
    QDateTime getWhenLiked() const;
};

#endif // LIKE_H
