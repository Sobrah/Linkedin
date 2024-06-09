#include "Headers/me.h"
#include <QSqlQuery>
#include "Headers/utility.h"
#include "ui_me.h"

Me::Me(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Me)
{
    ui->setupUi(this);

    // Initialize Information
    POOL->start([=] { queryInformation(); });

    qDebug("Me Starts.");
}

Me::~Me()
{
    delete ui;
    qDebug("Me Ends.");
}

void Me::queryInformation()
{
    QSqlQuery query;
    query.prepare("SELECT username FROM accounts WHERE accountID = ?");
    query.addBindValue(ACCOUNT_ID);
    query.exec();
    query.first();

    ui->usernameLabel->setText(query.value("username").toString());
}
