#include "Headers/splash.h"
#include "Headers/login.h"

#include "ui_splash.h"

Splash::Splash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Splash)
{
    ui->setupUi(this);
}

Splash::~Splash()
{
    delete ui;
}

void Splash::on_loginButton_clicked()
{
    Login *w = new Login;
    w->show();

    close();
}

