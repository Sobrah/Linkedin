#ifndef LIKE_H
#define LIKE_H

#include <QObject>
#include <QSqlQuery>
#include "Headers/time.h"

class Like : public QObject
{
    Q_OBJECT

public:
    explicit Like(QObject * = nullptr);
    ~Like();

    void deleteLike(int);
    void insertLike(int);
    bool selectHasLike(int);
    QVector<int> selectLikesBasePost(int);
    int selectCountPostLikes(int);

    // Setters
    void setLikeID(int);
    void setWhoLikedID(int);
    void setPostID(int);

    // Getters
    int getLikeID() const;
    int getWhoLikedID() const;
    int getPostID() const;
    Time getTimeLiked() const;

private:
    int likeID = false;
    int whoLikedID = false;
    int postID = false;
    Time timeLiked;
};

#endif // LIKE_H
