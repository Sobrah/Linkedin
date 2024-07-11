#include <QApplication>
#include <Header>

QWidget *FRAME;
Account *ACCOUNT;
QThreadPool *POOL;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initialize Window Frame
    FRAME = new Window;
    FRAME->show();

    // Database Thread Pool
    POOL = new QThreadPool(FRAME);
    POOL->setMaxThreadCount(1);
    POOL->setExpiryTimeout(-1);

    // Initialize Database
    POOL->start(initializeDatabase);

    // Initialize User Account
    ACCOUNT = new Account(FRAME);

    // Initialize First Page
    decideInitialPage();

    return app.exec();
}
