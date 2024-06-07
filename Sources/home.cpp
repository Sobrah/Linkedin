#include <QSqlQuery>
#include <QtConcurrentRun>

#include "Headers/home.h"
#include "Headers/jobcompany.h"
#include "Headers/me.h"
#include "Headers/post.h"
#include "Headers/window.h"
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
    connect(ui->homeButton, &QPushButton::clicked, this, [=] {
        Window::changePage(new Home, parentWidget());
    });

    // Switch Job Page
    connect(ui->jobButton, &QPushButton::clicked, this, [=] {
        if (IS_COMPANY)
            Window::changePage(new JobCompany, ui->containerGroup);
    });

    // Switch Me Page
    connect(ui->userButton, &QPushButton::clicked, this, [=] {
        Window::changePage(new Me, ui->containerGroup);
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
