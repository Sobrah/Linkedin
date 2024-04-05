#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QWidget>

namespace Ui {
class Verification;
}

class Verification : public QWidget
{
    Q_OBJECT

public:
    explicit Verification(int, QWidget *parent = nullptr);
    ~Verification();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::Verification *ui;
    int verificationCode;
};

#endif // VERIFICATION_H
