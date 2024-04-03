#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>

namespace Ui {
class Splash;
}

class Splash : public QWidget
{
    Q_OBJECT

public:
    explicit Splash(QWidget *parent = nullptr);
    ~Splash();

private slots:
    void on_startButton_clicked();

private:
    Ui::Splash *ui;
};
#endif // SPLASH_H
