#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H

#include <QWidget>
#include <Header>

namespace Ui {
class NetworkRequest;
}

class NetworkRequest : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkRequest(int, QWidget *parent = nullptr);
    ~NetworkRequest();

private:
    void acceptButtonClicked();
    void rejectButtonClicked();

    Ui::NetworkRequest *ui;
    Account *account;
};

#endif // NETWORKREQUEST_H
