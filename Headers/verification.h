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
    explicit Verification(QString &, QString &, QByteArray &, QWidget *parent = nullptr);
    ~Verification();

private:
    void confirmButtonClicked();

    Ui::Verification *ui;
    QString code;
    QString username;
    QByteArray password;
};

#endif // VERIFICATION_H
