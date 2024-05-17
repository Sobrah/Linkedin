#include <QFile>
#include <QMessageBox>
#include <QValidator>

#include "Headers/profile.h"
#include "Headers/verification.h"
#include "Headers/window.h"
#include "ui_verification.h"

Verification::Verification(QString &code, QString &username, QByteArray &password, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Verification)
    , code(code)
    , username(username)
    , password(password)
{
    ui->setupUi(this);
    ui->codeEdit->setValidator(new QIntValidator);

    // Confirm Button Clicked
    connect(ui->confirmButton, &QPushButton::clicked, this, &Verification::confirmButtonClicked);

    qDebug() << "Verification Starts.";
}

Verification::~Verification()
{
    delete ui;
    qDebug() << "Verification Ends.";
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
    QFile file("session");
    file.open(QIODevice::WriteOnly);

    QDataStream stream(&file);
    stream << username << password;

    // Show Profile Page
    Window::changePage(new Profile, parentWidget());
}
