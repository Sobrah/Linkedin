#ifndef COLLECTION_H
#define COLLECTION_H

#include <QWidget>

namespace Ui {
class Collection;
}

class Collection : public QWidget
{
    Q_OBJECT

public:
    explicit Collection(QWidget *parent = nullptr);
    ~Collection();

private:
    Ui::Collection *ui;
};

#endif // COLLECTION_H
