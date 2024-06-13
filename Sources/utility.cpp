#include <QBoxLayout>
#include <QFile>
#include <QProcessEnvironment>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QThreadPool>
#include <QWidget>
#include <QtMath>

#include "Headers/account.h"
#include "Headers/home.h"
#include "Headers/splash.h"
#include "Headers/utility.h"

void initializeDatabase()
{
    // Initialize Environmental Variables
    auto env = QProcessEnvironment::systemEnvironment();

    // Initialize Database
    auto db = QSqlDatabase::addDatabase(env.value("DATABASE_TYPE"));
    db.setDatabaseName(env.value("DATABASE_NAME"));
    db.setHostName(env.value("DATABASE_HOST"));
    db.setUserName(env.value("DATABASE_USER"));
    db.setPassword(env.value("DATABASE_PASSWORD"));

    // Invalid Database
    if (!db.isValid()) {
        qDebug("Database Is Not Valid.");
        throw;
    }

    db.open();

    // Cannot Open Database
    if (!db.isOpen()) {
        qDebug("Cannot Open Database.");
        throw;
    }

    qDebug("Database Initialized.");
}

bool checkSession()
{
    QFile file("Session");

    // Open File
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QString username;
    QByteArray password;
    QDataStream stream(&file);
    stream >> username >> password;

    ACCOUNT->setUsername(username);
    ACCOUNT->setPassword(password);
    ACCOUNT->getInformation();

    // Invalid Account
    if (!ACCOUNT->getAccountID())
        return false;

    return true;
}

void changePage(QWidget *page, QWidget *parent)
{
    auto children = parent->findChildren<QWidget *>();
    foreach (auto widget, children) {
        widget->hide();
        widget->deleteLater();
    }

    parent->layout()->addWidget(page);
    page->show();
}

void decideInitialPage()
{
    RUN(POOL, checkSession).then(FRAME, [=](bool session) {
        QWidget *page;
        if (session)
            page = new Home;
        else
            page = new Splash;
        changePage(page, FRAME);
    });
}

QString generateCode(int digits)
{
    int max = qPow(10, digits) - 1;

    auto n = QRandomGenerator::global()->bounded(0, max);
    auto code = QString::number(n).rightJustified(digits, '0');

    return code;
}
