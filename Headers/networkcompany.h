#ifndef NETWORKCOMPANY_H
#define NETWORKCOMPANY_H

#include <QWidget>

namespace Ui {
class NetworkCompany;
}

class NetworkCompany : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkCompany(QWidget *parent = nullptr);
    ~NetworkCompany();

private:
    Ui::NetworkCompany *ui;
};

#endif // NETWORKCOMPANY_H
