#include "Headers/like.h"

void Like::setWhoLikedId(int whoLikedId)
{
    Like::whoLikedId = whoLikedId;
}

void Like::setLikeId(int likeId)
{
    Like::likeId = likeId;
}

void Like::setWhenLiked(QDateTime whenLiked)
{
    Like::whenLiked = whenLiked;
}

int Like::getWhoLikedId() const
{
    return whoLikedId;
}

int Like::getLikeId() const
{
    return likeId;
}

QDateTime Like::getWhenLiked() const
{
    return whenLiked;
}
