#include <QApplication>

#include "Headers/utility.h"
#include "Headers/window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initialize Window Frame
    auto frame = new Window;
    frame->show();

    // Database Thread Pool
    POOL = new QThreadPool(frame);
    POOL->setMaxThreadCount(1);
    POOL->setExpiryTimeout(-1);

    // Initialize Database
    POOL->start(initializeDatabase);

    // Initialize First Page
    decideInitialPage(frame);

    return app.exec();
}
