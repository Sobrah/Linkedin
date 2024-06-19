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
    explicit Collection(int, QWidget *parent = nullptr);
    ~Collection();

private:
    Ui::Collection *ui;
    Post *post;
    Account *account;
    bool hasConnection;
};

#endif // COLLECTION_H
