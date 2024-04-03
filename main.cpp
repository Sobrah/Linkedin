#include <QApplication>

#include "Headers/window.h"
#include "Headers/splash.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;

    window.switchPage(new Splash);

    window.show();
    return app.exec();
}
