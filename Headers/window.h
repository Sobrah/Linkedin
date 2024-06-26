#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    static void changePage(QWidget *, QWidget *);
    ~Window();

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
