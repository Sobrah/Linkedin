#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProcessEnvironment>
#include <QValidator>

#include "Headers/profile.h"
#include "Headers/utility.h"
#include "Headers/verification.h"
#include "ui_verification.h"

Verification::Verification(Account *account, bool formStatus, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Verification)
    , account(account)
    , code(generateCode())
    , formStatus(formStatus)
{
    ui->setupUi(this);
    ui->codeEdit->setValidator(new QIntValidator);

    // Send Email
    sendEmail(account->getEmail(), code);

    // Confirm Button Clicked
    connect(ui->confirmButton, &QPushButton::clicked, this, &Verification::confirmButtonClicked);

    qDebug("Verification Starts With Code %d.", code.toInt());
}

Verification::~Verification()
{
    delete ui;
    qDebug("Verification Ends.");
}

void Verification::confirmButtonClicked()
{
    if (ui->codeEdit->text() != code) {
        QMessageBox box;
        QMessageBox::warning(&box, "Verification Code", "Verification Code Is Not Correct.");
        ui->codeEdit->setText("");
        return;
    }

    // Create Session
    QFile file("Session");
    file.open(QIODevice::WriteOnly);

    QDataStream stream(&file);
    stream << account->getUsername() << account->getPassword();

    if (formStatus) {
        decideInitialPage(parentWidget());
    } else {
        changePage(new Profile(account), parentWidget());
    }
}

void Verification::sendEmail(QString to, QString code)
{
    // Initialize Environmental Variables
    auto env = QProcessEnvironment::systemEnvironment();

    // Initialize Network Manager
    auto *manager = new QNetworkAccessManager;

    // Print Response Message
    connect(manager, &QNetworkAccessManager::finished, manager, [](QNetworkReply *reply) {
        QString data(reply->readAll());

        if (data.isEmpty())
            qDebug("Email Sent.");
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
