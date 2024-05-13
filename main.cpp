#include <QApplication>
#include <QProcessEnvironment>
#include <QSqlDatabase>
#include <QThreadPool>
#include <QtConcurrentRun>

#include "Headers/window.h"

QThreadPool *POOL;

void initializeDatabase()
{
    // Initialize Environmental Variables
    auto env = QProcessEnvironment::systemEnvironment();

    // Initialize Database
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName(env.value("PG_DATABASE"));
    db.setHostName(env.value("PG_HOST"));
    db.setUserName(env.value("PG_USER"));
    db.setPassword(env.value("PG_PASSWORD"));

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
    static_cast<void>(QtConcurrent::run(POOL, initializeDatabase));

    // Start Window Frame
    Window window;
    window.show();

    return app.exec();
}
