#include <QSqlQuery>
#include <QtConcurrentRun>

#include "Headers/me.h"
#include "Headers/window.h"
#include "ui_me.h"

me::me(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::me)
{
    ui->setupUi(this);
    static_cast<void>(QtConcurrent::run(POOL, me::queryInformation, this));
}

me::~me()
{
    delete ui;
}

void me::queryInformation()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE userID = ?");
    query.addBindValue(USER_ID);
    query.exec();
    query.first();
    ui->usernameLabel->setText(query.value("username").toString());
}
