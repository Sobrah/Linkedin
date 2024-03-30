#ifndef VERTIFICATION_H
#define VERTIFICATION_H

#include <QMainWindow>

namespace Ui {
class Vertification;
}

class Vertification : public QMainWindow
{
    Q_OBJECT

public:
    explicit Vertification(QWidget *parent = nullptr);
    ~Vertification();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::Vertification *ui;
};

#endif // VERTIFICATION_H
