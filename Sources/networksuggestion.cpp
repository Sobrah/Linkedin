#include <QMessageBox>
#include "ui_networksuggestion.h"
#include <Header>

NetworkSuggestion::NetworkSuggestion(int accountID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkSuggestion)
    , account(new Account)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        account->setAccountID(accountID);
        account->selectAccountBaseID();
    }).then(this, [=] { ui->usernameLabel->setText(account->getUsername()); });

    connect(ui->connectButton,
            &QPushButton::clicked,
            this,
            &NetworkSuggestion::connectButtonClicked);

    connect(ui->viewProfileButton,
            &QPushButton::clicked,
            this,
            &NetworkSuggestion::viewProfileButtonClicked);

    qDebug("Network Suggestion Starts.");
}

NetworkSuggestion::~NetworkSuggestion()
{
    delete ui;
    qDebug("Network Suggestion Ends.");
}

void NetworkSuggestion::connectButtonClicked()
{
    RUN(POOL, [=] { ACCOUNT->insertConnectionRequest(account->getAccountID()); }).then(this, [=] {
        QMessageBox::warning(this, "Connection Request", "Connection Request Sent");
    });
}

void NetworkSuggestion::viewProfileButtonClicked()
{
    int accountID = account->getAccountID();
    changePage(new ViewProfile(accountID), FRAME);
}
