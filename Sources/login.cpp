#include "Headers/login.h"
#include "Headers/verification.h"

#include "ui_login.h"

#include <QDebug>
#include <QProcessEnvironment>

#include <QSqlDatabase>
#include <QSqlQuery>

#include "QMessageBox"
#include "QValidator"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    // Produce random number
    int randomNum;
    randomNum = rand()%9000+1000;
    ui->captcha2Label->setText(QString::number(randomNum));

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

    //Setting echo mode for password label
    ui->passwordLabel->setEchoMode(QLineEdit::Password);

    ui->codeLabel->setValidator(new QIntValidator);
}

Login::~Login()
{
    delete ui;
}

void Login::on_verificationButton_clicked()
{

    QString username = ui->usernameLabel->text();
    QString password = ui->passwordLabel->text();
    QString s;

    int passwordLength = password.size();
    int usernamelength = username.size();
    int randomNum;
    int sw;

    QSqlQuery q;

    if(ui->signButton->text() == "Login"){

        sw = 0;

        //Check the size of password
        if(passwordLength<4){
            QMessageBox::warning(this,"Eror!","Your password should have at least 4 digits !");
            ui->passwordLabel->setText("");
            ui->passwordLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
        }
        else sw++;

        //Check the size of username
        if(usernamelength<8){
            QMessageBox::warning(this,"Eror!","Your username should have at least 8 characters !");
            ui->usernameLabel->setText("");
            ui->usernameLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
        }
        else sw++;

        //Check the captcha code
        if(ui->captcha2Label->text() != ui->codeLabel->text()){
            QMessageBox::warning(this,"Eror!","Enter the number correctly !");
            randomNum = rand()%9000+1000;
            ui->captcha2Label->setText(QString::number(randomNum));
            ui->codeLabel->setText("");
            ui->codeLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
        }
        else sw++;

        //Check the uniqueness of username
        if(sw==3){
            q.exec("SELECT username FROM users WHERE username='"+username+"'");
            if(q.first()){
                QMessageBox::warning(this,"Eror","Your username is already taken , please enter another one !");
            }
            else{
                q.exec("INSERT INTO users(username,password)VALUES('"+username+"','"+password+"')");
                sw++;
            }
        }

        //show the new page
        if(sw==4){
            Verification *w = new Verification;
            w->show();

            close();
        }
    }
    else if(ui->signButton->text() == "Sign Up"){

        sw = 0;

        //Check the captcha code
        if(ui->captcha2Label->text() != ui->codeLabel->text()){
            QMessageBox::warning(this,"Eror!","Enter the number correctly !");
            randomNum = rand()%9000+1000;
            ui->captcha2Label->setText(QString::number(randomNum));
            ui->codeLabel->setText("");
            ui->codeLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
        }
        else sw++;


        q.exec("SELECT password FROM users WHERE username='"+username+"'");
        if(q.first()){
            s = q.value(0).toString();
            if(s == password){
                sw++;
            }
            else{
                QMessageBox::warning(this,"Eror","Your password is incorrect !");
                ui->passwordLabel->setText("");
                ui->passwordLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
            }
        }
        else{
            QMessageBox::warning(this,"Eror","Your username is incorrect !");
            ui->usernameLabel->setText("");
            ui->passwordLabel->setText("");
            ui->usernameLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
            ui->passwordLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
        }

        //Show the new page
        if(sw==2){
            Verification *w = new Verification;
            w->show();

            close();
        }
    }
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
    ui->usernameLabel->setText("");
    ui->passwordLabel->setText("");
    ui->codeLabel->setText("");

    //Change the captcha code
    int randomNum;
    randomNum = rand()%9000+1000;
    ui->captcha2Label->setText(QString::number(randomNum));

}

