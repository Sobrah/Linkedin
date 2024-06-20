#ifndef VIEWPOST_H
#define VIEWPOST_H

#include <QWidget>

namespace Ui {
class ViewPost;
}

class ViewPost : public QWidget
{
    Q_OBJECT

public:
    explicit ViewPost(int, QWidget *parent = nullptr);
    ~ViewPost();

private:
    Ui::ViewPost *ui;
};

#endif // VIEWPOST_H
