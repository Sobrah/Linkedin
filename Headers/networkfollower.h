#ifndef NETWORKFOLLOWER_H
#define NETWORKFOLLOWER_H

#include <QWidget>

namespace Ui {
class NetworkFollower;
}

class NetworkFollower : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkFollower(int, QWidget *parent = nullptr);
    ~NetworkFollower();

private:
    Ui::NetworkFollower *ui;
};

#endif // NETWORKFOLLOWER_H
