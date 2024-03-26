#ifndef SPLASH_H
#define SPLASH_H

#include <QMainWindow>

namespace Ui {
class Splash;
}

class Splash : public QMainWindow
{
    Q_OBJECT

public:
    Splash(QWidget *parent = nullptr);
    ~Splash();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Splash *ui;
};
#endif // SPLASH_H
