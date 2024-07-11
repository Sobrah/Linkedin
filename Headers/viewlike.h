#ifndef VIEWLIKE_H
#define VIEWLIKE_H

#include <QWidget>
#include <Logics>

namespace Ui {
class ViewLike;
}

class ViewLike : public QWidget
{
    Q_OBJECT

public:
    explicit ViewLike(int, QWidget *parent = nullptr);
    ~ViewLike();

private:
    Ui::ViewLike *ui;
    Account *account;
};

#endif // VIEWLIKE_H
