#include <QLabel>
#include <Logics>
#include <Views>

NetworkCompany::NetworkCompany(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkCompany)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        Account account;
        return account.selectFollowers();
    }).then(this, [=](QVector<int> followers) {
        foreach (auto followerID, followers) {
            ui->verticalLayout->addWidget(new NetworkFollower(followerID));
        }
    });

    qDebug("Network Company Starts.");
}

NetworkCompany::~NetworkCompany()
{
    delete ui;
    qDebug("Network Company ends.");
}
