#include "ui_networkrequest.h"
#include <Header>

NetworkRequest::NetworkRequest(int followerID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkRequest)
    , account(new Account)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        account->setAccountID(followerID);
        account->selectAccountBaseID();
    }).then(this, [=] { ui->usernameLabel->setText(account->getUsername()); });

    connect(ui->acceptButton, &QPushButton::clicked, this, &NetworkRequest::acceptButtonClicked);

    connect(ui->rejectButton, &QPushButton::clicked, this, &NetworkRequest::rejectButtonClicked);
}

NetworkRequest::~NetworkRequest()
{
    delete ui;
    delete account;
}

void NetworkRequest::acceptButtonClicked()
{
    RUN(POOL, [=] {
        account->insertConnection(ACCOUNT->getAccountID());
        account->deleteConnectionRequest(ACCOUNT->getAccountID());
    }).then([=] { deleteLater(); });
}

void NetworkRequest::rejectButtonClicked()
{
    RUN(POOL, [=] { account->deleteConnectionRequest(ACCOUNT->getAccountID()); }).then([=] {
        deleteLater();
    });
}
