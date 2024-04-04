#include "Headers/login.h"
#include "Headers/verification.h"

#include "ui_login.h"

#include <QDebug>
#include <QProcessEnvironment>

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <QMessageBox>
#include <QValidator>

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
    QString code = ui->codeLabel->text();
    QString email = ui->emailLabel->text();
    QString s;

    int passwordLength = password.size();
    int usernamelength = username.size();
    int codelength = code.size();
    int emaillength = email.size();
    int randomNum;
    int randomNum_2;

    QSqlQuery q;

    if(ui->signButton->text() == "Login"){

        //Check if all the lines are empty
        if( usernamelength == 0 && passwordLength == 0 && codelength == 0 && emaillength == 0){
            QMessageBox::warning(this,"Eror !","You should compelete the requested items !");
            return ;
        }

        //Check if the emailLabel is empty
        if(emaillength == 0){
            QMessageBox::warning(this,"Eror","You should enter your email !");
            return ;
        }

        //Check the size of username
        if(usernamelength<4){
            QMessageBox::warning(this,"Eror!","Your username should have at least 4 characters !");
            ui->usernameLabel->setText("");
            ui->usernameLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
            return ;
        }

        //Check the size of password
        if(passwordLength<4){
            QMessageBox::warning(this,"Eror!","Your password should have at least 4 characters !");
            ui->passwordLabel->setText("");
            ui->passwordLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
            return ;
        }

        //Check the captcha code
        if(ui->captcha2Label->text() != code){
            QMessageBox::warning(this,"Eror!","Enter the number correctly !");
            randomNum = rand()%9000+1000;
            ui->captcha2Label->setText(QString::number(randomNum));
            ui->codeLabel->setText("");
            ui->codeLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
            return ;
        }

        //Check the uniqueness of username
        q.exec("SELECT username FROM users WHERE username='"+username+"'");
        if(q.first()){
            QMessageBox::warning(this,"Eror","Your username is already taken , please enter another one !");
            return ;
        }

        //Check the uniqueness of email
        q.exec("SELECT email FROM users WHERE email='"+email+"'");
        if(q.first()){
            QMessageBox::warning(this,"Eror","Your email is already taken , please enter another one !");
            return ;
        }
        if(!q.first()){
            q.exec("INSERT INTO users(username,password,email)VALUES('"+username+"','"+password+"','"+email+"')");
        }

        //Sending the verification code to the email
        randomNum_2 = rand() % 9000 + 1000;
        sendEmail("Welcome to linkedin , Your verification code is " + QString::number(randomNum_2) + " .");

        //show the new page
        Verification *w = new Verification;
        w->show();

        close();
        return ;
    }

    if(ui->signButton->text() == "Sign Up"){

        if( usernamelength == 0 && passwordLength == 0 && codelength == 0){
             QMessageBox::warning(this,"Eror !","You should compelete the requested items !");
            return ;
        }

        //Check the captcha code
         if(ui->captcha2Label->text() != ui->codeLabel->text()){
            QMessageBox::warning(this,"Eror!","Enter the number correctly !");
            randomNum = rand()%9000+1000;
            ui->captcha2Label->setText(QString::number(randomNum));
            ui->codeLabel->setText("");
            ui->codeLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
            return ;
        }


        q.exec("SELECT password FROM users WHERE username='"+username+"'");
        if(q.first()){
            s = q.value(0).toString();
            if(s != password){
                QMessageBox::warning(this,"Eror","Your password is incorrect !");
                ui->passwordLabel->setText("");
                ui->passwordLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
                return ;
            }
        }
        if(!q.first()){
            QMessageBox::warning(this,"Eror","Your username is incorrect !");
            ui->usernameLabel->setText("");
            ui->passwordLabel->setText("");
            ui->usernameLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
            ui->passwordLabel->setStyleSheet("border-color: rgb(255, 0, 0);");
            return ;
        }

        //Show the new page
        sendEmail("Your Verification Code Is Unknown");

        Verification *w = new Verification;
        w->show();

        close();
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
    ui->emailLabel->setText("");

    //Change the captcha code
    int randomNum;
    randomNum = rand()%9000+1000;
    ui->captcha2Label->setText(QString::number(randomNum));

}

void Login::sendEmail(QString text) {
    QProcessEnvironment env;
    env = QProcessEnvironment::systemEnvironment();

    // Initialize Network Manager
    auto *manager = new QNetworkAccessManager(this);
    connect(
        manager,
        SIGNAL(finished(QNetworkReply *)),
        this,
        SLOT(checkResponse(QNetworkReply *))
    );

    // Initialize Network Request
    QUrl url(env.value("MAIL_HOST"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", env.value("MAIL_PASSWORD").toUtf8());

    // Create Json Request
    QJsonObject content;

    QJsonObject from;
    from.insert("email", env.value("MAIL_SENDER"));
    content.insert("from", from);

    QJsonArray receiver;
    QJsonObject to;
    to.insert("email", ui->emailLabel->text());
    receiver.append(to);

    content.insert("to", receiver);
    content.insert("subject", "Verification");
    content.insert("text", text);

    QJsonDocument document(content);
    QByteArray data(document.toJson());

    manager->post(request, data);
}

void Login::checkResponse(QNetworkReply *response) {
    qDebug() << response->readAll();
}
