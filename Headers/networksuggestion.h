#ifndef NETWORKSUGGESTION_H
#define NETWORKSUGGESTION_H

#include <QWidget>
#include <Logics>

namespace Ui {
class NetworkSuggestion;
}

class NetworkSuggestion : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkSuggestion(int, QWidget *parent = nullptr);
    ~NetworkSuggestion();

private:
    void connectButtonClicked();
    void viewProfileButtonClicked();

    Ui::NetworkSuggestion *ui;
    Account *account;
};

#endif // NETWORKSUGGESTION_H
