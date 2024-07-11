#ifndef COLLECTION_H
#define COLLECTION_H

#include <QWidget>
#include <Logics>

namespace Ui {
class Collection;
}

class Collection : public QWidget
{
    Q_OBJECT

public:
    explicit Collection(int, QWidget *, QWidget *parent = nullptr);
    ~Collection();

private:
    void followButtonClicked();
    void repostButtonClicked();
    void likeButtonClicked();

    Ui::Collection *ui;
    Post *post;
    Account *account;
    Like *like;
    bool hasConnection;
    bool hasLike;

    const QString connectionStatus[2] = {"Connect", "Connected"};
    const QString followingStatus[2] = {"Follow", "Followed"};
    const QString likeStatus[2] = {"Like", "Liked"};
};

#endif // COLLECTION_H
