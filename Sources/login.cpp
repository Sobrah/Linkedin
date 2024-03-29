#include "Headers/login.h"
#include "Headers/vertification.h"

#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_verificationButton_clicked()
{
    Vertification *w = new Vertification;
    w->show();

    close();
}

void Login::on_signButton_clicked()
{
    static int situation;

    const QString signs[2] = {
        "Login", "Sign Up"
    };
    const QString invitations[2] = {
        "Stay Updated On Your Professional World",
        "Make The Most Of Your Professional Life"
    };

    // Change invitation parts
    ui->descriptionLabel->setText(invitations[situation]);
    ui->signButton->setText(signs[situation]);

    // Change form parts
    situation = (situation + 1) % 2;
    ui->signLabel->setText(signs[situation]);
    ui->emailLabel->setEnabled(situation);
}

