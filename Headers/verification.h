#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QMainWindow>

namespace Ui {
class Verification;
}

class Verification : public QMainWindow
{
    Q_OBJECT

public:
    explicit Verification(QWidget *parent = nullptr);
    ~Verification();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::Verification *ui;
};

#endif // VERIFICATION_H
