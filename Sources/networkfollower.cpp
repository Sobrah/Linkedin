#include <Logics>
#include <Views>

NetworkFollower::NetworkFollower(int accountID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkFollower)
{
    ui->setupUi(this);

    POOL->start([=] {
        Account account;
        account.setAccountID(accountID);
        account.selectAccountBaseID();

        ui->usernameLabel->setText(account.getUsername());
    });

    connect(ui->viewProfileButton, &QPushButton::clicked, this, [=] {
        changePage(new ViewProfile(accountID), parentWidget()->parentWidget());
    });

    qDebug("Network Follower Starts.");
}

NetworkFollower::~NetworkFollower()
{
    delete ui;
    qDebug("Network Follower Ends.");
}
