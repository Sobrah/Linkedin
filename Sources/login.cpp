#include <QCryptographicHash>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlQuery>

#include "Headers/login.h"
#include "Headers/utility.h"
#include "Headers/verification.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->captchaLabel->setText(captchaCode());
    ui->codeLabel->setValidator(new QIntValidator);

    // Warn Message Emitted
    connect(this, &Login::warnMessage, this, [=](QString title, QString text) {
        QMessageBox box;
        QMessageBox::warning(&box, title, text);
        ui->captchaLabel->setText(captchaCode());
        ui->passwordLabel->setText("");
        ui->codeLabel->setText("");
    });

    // Verification Button Clicked
    connect(ui->verificationButton, &QPushButton::clicked, this, [=] {
        RUN(POOL, &Login::verificationButtonClicked, this).then(this, [=](bool status) {
            if (!status)
                return;

            changePage(new Verification(formStatus), FRAME);
        });
    });

    // Sign Button Clicked
    connect(ui->signButton, &QPushButton::clicked, this, &Login::signButtonClicked);

    qDebug("Login Starts.");
}

Login::~Login()
{
    delete ui;
    qDebug("Login Ends.");
}

bool Login::verificationButtonClicked()
{
    QString email = ui->emailLabel->text();
    const QString username = ui->usernameLabel->text();
    const QString password = ui->passwordLabel->text();
    const QString captcha = ui->captchaLabel->text();
    const QString code = ui->codeLabel->text();

    // Check Fields
    if (username.length() < 4) {
        emit warnMessage("Username Length", "Username Should Be At Least 4 Characters.");
        return false;
    }
    if (password.length() < 4) {
        emit warnMessage("Password Length", "Password Should Be At Least 4 Characters.");
        return false;
    }
    if (captcha != code) {
        emit warnMessage("Security Code", "Security Code Is Not Correct.");
        return false;
    }

    // Hash Password
    QCryptographicHash cryptoHash(QCryptographicHash::Sha256);
    cryptoHash.addData(password.toLocal8Bit());
    auto hashedPassword = cryptoHash.result();

    QSqlQuery query;
    if (formStatus) {
        query.prepare("SELECT email FROM accounts WHERE username = ? AND password = ?");
        query.addBindValue(username);
        query.addBindValue(hashedPassword);
        query.exec();

        // Invalid Credentials
        if (!query.first()) {
            emit warnMessage("Incorrect Values", "Username Or Password Is Incorrect.");
            return false;
        }
        email = query.value("email").toString();

    } else {
        query.prepare("SELECT username FROM accounts WHERE username = ?");
        query.addBindValue(username);
        query.exec();

        // Repetitive Username
        if (query.first()) {
            emit warnMessage("Username Value", "Username Has Been Taken, Choose Another One.");
            return false;
        }
    }

    // Initialize Account
    ACCOUNT->setUsername(username);
    ACCOUNT->setPassword(hashedPassword);
    ACCOUNT->setEmail(email);

    return true;
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
    ui->captchaLabel->setText(captchaCode());

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
