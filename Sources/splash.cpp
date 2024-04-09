#include "Headers/splash.h"
#include "Headers/login.h"
#include "Headers/window.h"
#include "ui_splash.h"

Splash::Splash(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Splash)
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, [=] {
        Window::changePage(new Login, parentWidget());
    });

    qDebug() << "Splash Starts.";
}

Splash::~Splash()
{
    delete ui;
    qDebug() << "Splash Ends.";
}
