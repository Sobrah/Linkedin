#include "Headers/window.h"
#include "Headers/login.h"
#include "Headers/verification.h"
#include "ui_login.h"

#include <QProcessEnvironment>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QValidator>
#include <QCryptographicHash>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
    , signStatus(SIGNUP)
{
    ui->setupUi(this);

    // Set Required Ui Fields
    resetCaptcha();
    ui->passwordLabel->setEchoMode(QLineEdit::Password);
    ui->codeLabel->setValidator(new QIntValidator);

    // Initialize Database
    if (!initDatabase())
    {
        QMessageBox::warning(
            this,
            "Database",
            "Cannot Connect To Database."
            );
    }

    qDebug() << "Login Starts.";
}

Login::~Login()
{
    delete ui;
    qDebug() << "Login Ends.";
}

void Login::on_verificationButton_clicked()
{
    QString email = ui->emailLabel->text();
    const QString username = ui->usernameLabel->text();
    const QString password = ui->passwordLabel->text();
    const QString captcha = ui->captchaLabel->text();
    const QString code = ui->codeLabel->text();

    if (username.length() < 4)
    {
        QMessageBox::warning(
            this,
            "Username Length",
            "Username Should Be At Least 4 Characters."
            );
        return;
    }
    if (password.length() < 4)
    {
        QMessageBox::warning(
            this,
            "Password Length",
            "Password Should Be At Least 4 Characters."
            );
        ui->passwordLabel->setText("");
        return;
    }
    if (captcha != code)
    {
        QMessageBox::warning(
            this,
            "Security Code",
            "Security Code Is Not Correct."
            );
        resetCaptcha();
        ui->codeLabel->setText("");
        return;
    }

    QSqlQuery query;

    // Hashing The Password
    QByteArray hash = QCryptographicHash::hash(password.toLocal8Bit() , QCryptographicHash::Sha256);

    if (signStatus == SIGNUP)
    {
        // Unique Username
        query.prepare("SELECT username FROM users WHERE username = ?");
        query.addBindValue(username);
        query.exec();

        if(query.first())
        {
            QMessageBox::warning(
                this,
                "Username Value",
                "Username Has Been Taken, Choose Another One."
                );
            return;
        }

        // Insert Information
        query.prepare("INSERT INTO users (username, password, email) VALUES (?, ?, ?)");
        query.addBindValue(username);
        query.addBindValue(hash);
        query.addBindValue(email);
        query.exec();
    }

    if (signStatus == LOGIN)
    {
        query.prepare("SELECT email FROM users WHERE username = ? AND password = ?");
        query.addBindValue(username);
        query.addBindValue(hash);
        query.exec();

        // Valid Credentials
        if (query.first())
        {
            email = query.value("email").toString();
        } else
        {
            QMessageBox::warning(
                this,
                "Incorrect Values",
                "Username Or Password Is Incorrect."
                );
            ui->passwordLabel->setText("");
            return;
        }
    }

    // Send Verification Code
    int verificationCode(fourDigitNumber());
    QString text("Welcome To Linkedin, Your Verification Code Is %1.");
    sendEmail(email, text.arg(verificationCode));

    // Show Verification Page
    hide();
    auto *window = static_cast<Window *> (parent());
    window->switchPage(new Verification(verificationCode));
    deleteLater();
}

void Login::on_signButton_clicked()
{
    const QString signs[2] = {
        "Sign Up", "Login"
    };
    const QString invitations[2] = {
        "Make The Most Of Your Professional Life.",
        "Stay Updated On Your Professional World."
    };

    // Reset Fields
    ui->emailLabel->setText("");
    ui->usernameLabel->setText("");
    ui->passwordLabel->setText("");
    ui->codeLabel->setText("");
    resetCaptcha();

    // Change Invitation Parts
    ui->descriptionLabel->setText(invitations[signStatus]);
    ui->signButton->setText(signs[signStatus]);

    // Change Form Parts
    signStatus = static_cast<Sign> ((signStatus + 1) % 2);
    ui->signLabel->setText(signs[signStatus]);
    if (signStatus)
        ui->emailLabel->hide();
    else
        ui->emailLabel->show();
}

void Login::sendEmail(QString to, QString text)
{
    // Initialize Environmental Variables
    QProcessEnvironment env;
    env = QProcessEnvironment::systemEnvironment();

    // Initialize Network Manager
    auto *manager = new QNetworkAccessManager;

    // Print Response Message
    connect(
        manager, &QNetworkAccessManager::finished,
        manager, [](QNetworkReply *reply)
        {
            QString data(reply->readAll());
            if (data.isEmpty())
                qDebug() << "Email Sent.";
            else
                qDebug() << data;
        });

    // Release Memory
    connect(
        manager, &QNetworkAccessManager::finished,
        manager, &QNetworkAccessManager::deleteLater
        );


    // Initialize Network Request
    QUrl url(env.value("MAIL_HOST"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", env.value("MAIL_PASSWORD").toUtf8());

    // Create Json Content
    QJsonObject content;

    QJsonObject from;
    from.insert("email", env.value("MAIL_SENDER"));
    content.insert("from", from);

    QJsonArray receivers;
    QJsonObject receiver;
    receiver.insert("email", to);
    receivers.append(receiver);

    content.insert("to", receivers);
    content.insert("subject", "Linkedin Verification");
    content.insert("text", text);

    QJsonDocument document(content);
    QByteArray data(document.toJson());

    manager->post(request, data);
}

bool Login::initDatabase()
{
    // Initialize Environmental Variables
    QProcessEnvironment env;
    env = QProcessEnvironment::systemEnvironment();

    // Initialize Database
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName(env.value("PG_DATABASE"));
    db.setHostName(env.value("PG_HOST"));
    db.setUserName(env.value("PG_USER"));
    db.setPassword(env.value("PG_PASSWORD"));

    // Invalid Database
    if (!db.isValid()) {
        qDebug() << "Database Is Not Valid.";
        return false;
    }

    db.open();

    // Cannot Open Database
    if (!db.isOpen()) {
        qDebug() << "Cannot Open Database.";
        return false;
    }

    return true;
}

int Login::fourDigitNumber()
{
    return QRandomGenerator::global()->bounded(1000, 9999);
}

void Login::resetCaptcha()
{
    ui->captchaLabel->setText(QString::number(fourDigitNumber()));
}
