#include <QCryptographicHash>
#include <QIntValidator>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProcessEnvironment>
#include <QRandomGenerator>
#include <QSqlQuery>
#include <QtConcurrentRun>

#include "Headers/login.h"
#include "Headers/verification.h"
#include "Headers/window.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->captchaLabel->setText(fourRandomDigits());
    ui->codeLabel->setValidator(new QIntValidator);

    // Warn Message Emitted
    connect(this, &Login::warnMessage, this, [=](QString title, QString text) {
        QMessageBox box;
        QMessageBox::warning(&box, title, text);
        ui->captchaLabel->setText(fourRandomDigits());
        ui->passwordLabel->setText("");
        ui->codeLabel->setText("");
    });

    // Fields Verified Emitted
    connect(this,
            &Login::fieldsVerified,
            this,
            [=](QString email, QString username, QByteArray password) {
                auto code = fourRandomDigits();

                sendEmail(email, code);
                Window::changePage(new Verification(code, username, password), parentWidget());
            });

    // Verification Button Clicked
    connect(ui->verificationButton, &QPushButton::clicked, this, [=] {
        static_cast<void>(QtConcurrent::run(POOL, &Login::verificationButtonClicked, this));
    });

    // Sign Button Clicked
    connect(ui->signButton, &QPushButton::clicked, this, &Login::signButtonClicked);

    qDebug() << "Login Starts.";
}

Login::~Login()
{
    delete ui;
    qDebug() << "Login Ends.";
}

void Login::verificationButtonClicked()
{
    QString email = ui->emailLabel->text();
    const QString username = ui->usernameLabel->text();
    const QString password = ui->passwordLabel->text();
    const QString captcha = ui->captchaLabel->text();
    const QString code = ui->codeLabel->text();

    // Check Fields
    if (username.length() < 4) {
        emit warnMessage("Username Length", "Username Should Be At Least 4 Characters.");
        return;
    }
    if (password.length() < 4) {
        emit warnMessage("Password Length", "Password Should Be At Least 4 Characters.");
        return;
    }
    if (captcha != code) {
        emit warnMessage("Security Code", "Security Code Is Not Correct.");
        return;
    }

    // Hash Password
    QCryptographicHash cryptoHash(QCryptographicHash::Sha256);
    cryptoHash.addData(password.toLocal8Bit());
    QByteArray hashedPassword = cryptoHash.result();

    QSqlQuery query;
    if (formStatus) {
        query.prepare("SELECT email FROM users WHERE username = ? AND password = ?");
        query.addBindValue(username);
        query.addBindValue(hashedPassword);
        query.exec();

        // Invalid Credentials
        if (!query.first()) {
            emit warnMessage("Incorrect Values", "Username Or Password Is Incorrect.");
            return;
        }
        email = query.value("email").toString();

    } else {
        query.prepare("SELECT username FROM users WHERE username = ?");
        query.addBindValue(username);
        query.exec();

        // Repetitive Username
        if (query.first()) {
            emit warnMessage("Username Value", "Username Has Been Taken, Choose Another One.");
            return;
        }

        // Insert Information
        query.prepare("INSERT INTO users (username, password, email) VALUES (?, ?, ?)");
        query.addBindValue(username);
        query.addBindValue(hashedPassword);
        query.addBindValue(email);
        query.exec();
    }

    emit fieldsVerified(email, username, hashedPassword);
}

void Login::signButtonClicked()
{
    const QString signs[2] = {"Sign Up", "Login"};
    const QString invitations[2] = {"Make The Most Of Your Professional Life.",
                                    "Stay Updated On Your Professional World."};

    // Reset Fields
    ui->emailLabel->setText("");
    ui->usernameLabel->setText("");
    ui->passwordLabel->setText("");
    ui->codeLabel->setText("");
    ui->captchaLabel->setText(fourRandomDigits());

    // Change Invitation Parts
    ui->descriptionLabel->setText(invitations[formStatus]);
    ui->signButton->setText(signs[formStatus]);

    formStatus = (formStatus + 1) % 2;

    // Change Form Parts
    ui->signLabel->setText(signs[formStatus]);
    if (formStatus)
        ui->emailLabel->hide();
    else
        ui->emailLabel->show();
}

void Login::sendEmail(QString &to, QString &code)
{
    // Initialize Environmental Variables
    auto env = QProcessEnvironment::systemEnvironment();

    // Initialize Network Manager
    auto *manager = new QNetworkAccessManager;

    // Print Response Message
    connect(manager, &QNetworkAccessManager::finished, manager, [](QNetworkReply *reply) {
        QString data(reply->readAll());

        if (data.isEmpty())
            qDebug() << "Email Sent.";
        else
            qDebug() << data;
    });

    // Release Memory
    connect(manager, &QNetworkAccessManager::finished, manager, &QNetworkAccessManager::deleteLater);

    // Initialize Network Request
    QUrl url(env.value("MAIL_HOST"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", env.value("MAIL_PASSWORD").toLocal8Bit());

    // Create Json Content
    QJsonObject content;

    QJsonObject from;
    from.insert("email", env.value("MAIL_SENDER"));
    content.insert("from", from);

    QJsonArray receivers;
    QJsonObject receiver;
    receiver.insert("email", to);
    receivers.append(receiver);

    QString text = "Welcome To Linkedin, Your Verification Code Is %1.";
    content.insert("to", receivers);
    content.insert("subject", "Linkedin Verification");
    content.insert("text", text.arg(code));

    QJsonDocument document(content);
    QByteArray data(document.toJson());

    manager->post(request, data);
}

QString Login::fourRandomDigits()
{
    int n = QRandomGenerator::global()->bounded(0, 9999);
    return QString::number(n).rightJustified(4, '0');
}
