#ifndef POST_H
#define POST_H

#include "Headers/content.h"

class Post : public Content
{
public:
    explicit Post(const QString &);

    // Getters
    int getPostID() const;

private:
    int postID;
};

#endif // POST_H
