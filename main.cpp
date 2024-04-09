#include <QApplication>
#include <QHBoxLayout>

#include "Headers/splash.h"
#include "Headers/window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Window window;
    window.layout()->addWidget(new Splash);
    window.show();

    return app.exec();
}
