#include <QSqlQuery>
#include <QtConcurrentRun>

#include "Headers/home.h"
#include "Headers/jobcompany.h"
#include "Headers/jobperson.h"
#include "Headers/me.h"
#include "Headers/networkcompany.h"
#include "Headers/post.h"
#include "Headers/utility.h"
#include "ui_home.h"

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    // Send Post
    connect(ui->postButton, &QPushButton::clicked, this, &Home::postButtonClicked);

    // Search Username
    connect(ui->searchCombo, &QComboBox::currentTextChanged, this, [=](const QString &text) {
        POOL->start([=] { searchCurrentTextChanged(text); });
    });

    // Switch Home Page
    connect(ui->homeButton, &QPushButton::clicked, this, [=] { changePage(new Home, FRAME); });

    // Switch Job Page
    connect(ui->jobButton, &QPushButton::clicked, this, [=] {
        QWidget *page;

        if (ACCOUNT->getIsCompany())
            page = new JobCompany;
        else
            page = new JobPerson;

        changePage(page, ui->containerGroup);
    });

    // Switch Network Page
    connect(ui->networkButton, &QPushButton::clicked, this, [=] {
        QWidget *page;

        if (ACCOUNT->getIsCompany())
            page = new NetworkCompany;
        // else
        // page = new NetworkPerson;

        changePage(page, ui->containerGroup);
    });

    // Switch Me Page
    connect(ui->userButton, &QPushButton::clicked, this, [=] {
        changePage(new Me, ui->containerGroup);
    });

    qDebug("Home Starts.");
}

Home::~Home()
{
    delete ui;
    qDebug("Home Ends.");
}

void Home::postButtonClicked()
{
    POOL->start([&] { Post(ui->postTextEdit->toPlainText()); });
}

void Home::searchCurrentTextChanged(const QString &text)
{
    QSqlQuery query;
    query.prepare("SELECT username FROM accounts WHERE username LIKE ? LIMIT 5");
    query.addBindValue(text + '%');
    query.exec();

    while (query.next()) {
        ui->searchCombo->addItem(query.value("username").toString());
    }
}
