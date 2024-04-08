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
    explicit Verification(QString, QWidget *parent = nullptr);
    ~Verification();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::Verification *ui;
    QString verificationCode;
};

#endif // VERIFICATION_H
