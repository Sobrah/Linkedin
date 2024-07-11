#ifndef VIEWCOMMENT_H
#define VIEWCOMMENT_H

#include <QWidget>
#include <Logics>

namespace Ui {
class ViewComment;
}

class ViewComment : public QWidget
{
    Q_OBJECT

public:
    explicit ViewComment(int, QWidget *parent = nullptr);
    ~ViewComment();

private:
    Ui::ViewComment *ui;
    Account *account;
    Comment *comment;
};

#endif // VIEWCOMMENT_H
