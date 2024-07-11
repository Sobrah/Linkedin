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
    void selectConnections();

    Ui::NetworkCompany *ui;

signals:
    void addConnection(const QString &);
};

#endif // NETWORKCOMPANY_H
