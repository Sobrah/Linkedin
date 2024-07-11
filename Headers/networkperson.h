#ifndef NETWORKPERSON_H
#define NETWORKPERSON_H

#include <QWidget>

namespace Ui {
class NetworkPerson;
}

class NetworkPerson : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkPerson(QWidget *parent = nullptr);
    ~NetworkPerson();

private:
    Ui::NetworkPerson *ui;
};

#endif // NETWORKPERSON_H
