#include <QFile>
#include <QSqlQuery>
#include <QtConcurrentRun>

#include "Headers/home.h"
#include "Headers/splash.h"
#include "Headers/window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    // Add Initial Page
    RUN(POOL, checkSession).then(this, [=](bool status) {
        QWidget *page;
        if (status)
            page = new Home;
        else
            page = new Splash;
        changePage(page, this);
    });

    qDebug("Window Starts.");
}

Window::~Window()
{
    delete ui;
    qDebug("Window Ends.");
}

void Window::changePage(QWidget *page, QWidget *parent)
{
    auto children = parent->findChildren<QWidget *>();
    foreach (auto widget, children) {
        widget->hide();
        widget->deleteLater();
    }

    parent->layout()->addWidget(page);
    page->show();
}

bool Window::checkSession()
{
    QFile file("session");

    // Open File
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QString username;
    QByteArray hashedPassword;

    QDataStream stream(&file);
    stream >> username >> hashedPassword;

    QSqlQuery query;
    query.prepare("SELECT accountID, isCompany FROM accounts WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(hashedPassword);
    query.exec();

    // Invalid Credentials
    if (!query.first())
        return false;

    // Key Part Of Session
    ACCOUNT_ID = query.value("accountID").toInt();
    IS_COMPANY = query.value("isCompany").toBool();

    return true;
}
