#ifndef POST_H
#define POST_H

#include <Header>

class Post : public Content
{
public:
    explicit Post(const QString &);

    // Getters
    int getPostID() const;

private:
    int postID = false;
};

#endif // POST_H
