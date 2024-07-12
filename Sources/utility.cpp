#include <QBoxLayout>
#include <QFile>
#include <QProcessEnvironment>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QThreadPool>
#include <QWidget>
#include <QtMath>
#include <Logics>
#include <Views>

void initializeDatabase()
{
    // Initialize Environmental Variables
    auto env = QProcessEnvironment::systemEnvironment();
    auto dbType = env.value("DATABASE_TYPE");
    auto dbName = env.value("DATABASE_NAME");
    auto dbHost = env.value("DATABASE_HOST");
    auto dbUsername = env.value("DATABASE_USER");
    auto dbPassword = env.value("DATABASE_PASSWORD");

    // Initialize Database
    auto db = QSqlDatabase::addDatabase(dbType);
    db.setDatabaseName(dbName);
    db.setHostName(dbHost);
    db.setUserName(dbUsername);
    db.setPassword(dbPassword);

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

    // Read Information
    QString username;
    QByteArray password;
    QDataStream stream(&file);
    stream >> username >> password;

    // Fetch Account Information
    ACCOUNT->setUsername(username);
    ACCOUNT->setPassword(password);
    ACCOUNT->selectAccountBaseUsername();

    // Valid Account
    if (ACCOUNT->getAccountID())
        return true;

    return false;
}

void changePage(QWidget *page, QWidget *parent)
{
    auto children = parent->findChildren<QWidget *>();

    // Hide Children
    foreach (auto widget, children) {
        widget->hide();
        widget->deleteLater();
    }

    // Show Page
    if (!parent->layout()) {
        qDebug("Invalid Layout.");
        return;
    }

    parent->layout()->addWidget(page);
    page->show();
}

void decideInitialPage()
{
    RUN(POOL, checkSession).then(FRAME, [](bool session) {
        if (session)
            changePage(new Home, FRAME);
        else
            changePage(new Splash, FRAME);
    });
}

bool executeQuery(QSqlQuery &db, const QString &query, const QVariantList &values)
{
    // Prepare Query
    if (!db.prepare(query)) {
        qDebug("Invalid Preparation");
        throw;
    }

    // Bind Values
    foreach (auto value, values) {
        db.addBindValue(value);
    }

    // Execute Query
    if (!db.exec()) {
        qDebug("Invalid Query.");
        throw;
    }

    return db.first();
}

QString captchaCode(int digits)
{
    int highest = qPow(10, digits) - 1;

    // Random Number
    auto number = QRandomGenerator::global()->bounded(highest);

    // Fix Code Length
    auto code = QString::number(number).rightJustified(digits, '0');

    return code;
}
