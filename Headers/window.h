#ifndef WINDOW_H
#define WINDOW_H

#include <QThreadPool>
#include <QWidget>
#include <QtConcurrentRun>

#define RUN QtConcurrent::run

extern int USER_ID;
extern QThreadPool *POOL;

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
    static void changePage(QWidget *, QWidget *);
    static bool checkSession();

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
