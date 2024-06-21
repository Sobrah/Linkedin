#ifndef COLLECTION_H
#define COLLECTION_H

#include <QWidget>
#include "Headers/account.h"
#include "Headers/post.h"

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

    Ui::Collection *ui;
    Post *post;
    Account *account;
    bool hasConnection;

    const QString connectionStatus[2] = {"Connect", "Connected"};
    const QString followingStatus[2] = {"Follow", "Followed"};
};

#endif // COLLECTION_H
