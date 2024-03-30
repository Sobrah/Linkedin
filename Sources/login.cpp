#include "Headers/login.h"
#include "Headers/vertification.h"

#include "ui_login.h"

#include <QDebug>
#include <QProcessEnvironment>

#include <QSqlDatabase>
#include <QSqlQuery>

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    // Initialize environmental variables
    QProcessEnvironment env;
    env = QProcessEnvironment::systemEnvironment();

    // Initialize database
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName(env.value("PGDATABASE"));
    db.setHostName(env.value("PGHOST"));
    db.setUserName(env.value("PGUSER"));
    db.setPassword(env.value("PGPASSWORD"));

    // Invalid database
    if (!db.isValid()) {
        qDebug() << "Database Is Not Valid.";
        throw;
    }

    db.open();

    // Cannot open database
    if (!db.isOpen()) {
        qDebug() << "Can Not Open Database.";
        throw;
    }
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

