#include <QApplication>
#include <QProcessEnvironment>
#include <QSqlDatabase>
#include <QThreadPool>
#include <QtConcurrentRun>

#include "Headers/window.h"

int USER_ID;
QThreadPool *POOL;

void initializeDatabase()
{
    // Initialize Environmental Variables
    auto env = QProcessEnvironment::systemEnvironment();

    // Initialize Database
    QSqlDatabase db = QSqlDatabase::addDatabase(env.value("DATABASE_TYPE"));
    db.setDatabaseName(env.value("DATABASE_NAME"));
    db.setHostName(env.value("DATABASE_HOST"));
    db.setUserName(env.value("DATABASE_USER"));
    db.setPassword(env.value("DATABASE_PASSWORD"));

    // Invalid Database
    if (!db.isValid()) {
        qDebug() << "Database Is Not Valid.";
        throw;
    }

    db.open();

    // Cannot Open Database
    if (!db.isOpen()) {
        qDebug() << "Cannot Open Database.";
        throw;
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Database Thread Pool
    QThreadPool pool;
    pool.setMaxThreadCount(1);
    pool.setExpiryTimeout(-1);
    POOL = &pool;

    // Initialize Database
    QtConcurrent::run(POOL, initializeDatabase).then([] { qDebug() << "Database Initialized."; });

    // Start Window Frame
    Window window;
    window.show();

    return app.exec();
}
