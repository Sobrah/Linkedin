#ifndef VIEWPOST_H
#define VIEWPOST_H

#include <QWidget>
#include <Header>

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
    void sendCommentButtonClicked();

    Ui::ViewPost *ui;
    Account *account;
    Post *post;
};

#endif // VIEWPOST_H
