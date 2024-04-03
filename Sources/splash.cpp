#include "Headers/window.h"
#include "Headers/splash.h"
#include "Headers/login.h"
#include "ui_splash.h"

#include <QHBoxLayout>

Splash::Splash(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Splash)
{
    ui->setupUi(this);
    qDebug() << "Splash Starts.";
}

Splash::~Splash()
{
    delete ui;
    qDebug() << "Splash Ends.";
}

void Splash::on_startButton_clicked()
{
    deleteLater();
    ((Window *) parent())->switchPage(new Login);
}
