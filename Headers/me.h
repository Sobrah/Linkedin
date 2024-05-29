#ifndef ME_H
#define ME_H

#include <QWidget>

namespace Ui {
class me;
}

class me : public QWidget
{
    Q_OBJECT

public:
    explicit me(QWidget *parent = nullptr);
    ~me();

private:
    void queryInformation();

    Ui::me *ui;
};

#endif // ME_H
