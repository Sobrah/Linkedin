#include <Logics>
#include <Views>

ViewLike::ViewLike(int accountID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewLike)
    , account(new Account)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        account->setAccountID(accountID);
        account->selectAccountBaseID();
    }).then(this, [=] { ui->usernameLabel->setText(account->getUsername()); });

    qDebug("View Like Starts.");
}

ViewLike::~ViewLike()
{
    delete ui;
    delete account;
    qDebug("View Like Ends.");
}
