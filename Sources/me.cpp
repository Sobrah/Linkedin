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

    // Save Button Clicked
    connect(ui->saveButton, &QPushButton::clicked, this, [=] {
        POOL->start([=] { saveButtonClicked(); });
    });

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
    query.prepare("SELECT * FROM accounts WHERE accountID = ?");
    query.addBindValue(ACCOUNT->getAccountID());
    query.exec();
    query.first();

    ui->usernameLabel->setText(query.value("username").toString());
    ui->skillLabel->setText(query.value("skill").toString());
    ui->bioEdit->setPlainText(query.value("bio").toString());
}

void Me::saveButtonClicked()
{
    const QString bio = ui->bioEdit->toPlainText();
    QSqlQuery query;
    query.prepare("UPDATE accounts SET bio = ? WHERE accountID = ?");
    query.addBindValue(bio);
    query.addBindValue(ACCOUNT->getAccountID());
    query.exec();
}
