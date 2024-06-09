#ifndef WINDOW_H
#define WINDOW_H

#include <QCloseEvent>
#include <QWidget>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
