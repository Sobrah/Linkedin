#include "Headers/window.h"
#include "Headers/verification.h"
#include "Headers/profile.h"
#include "ui_verification.h"

#include <QMessageBox>
#include <QValidator>

Verification::Verification(QString code, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Verification)
    , verificationCode(code)
{
    ui->setupUi(this);
    ui->codeEdit->setValidator(new QIntValidator);

    qDebug() << "Verification Starts.";
}

Verification::~Verification()
{
    delete ui;
    qDebug() << "Verification Ends";
}

void Verification::on_confirmButton_clicked()
{
    if (ui->codeEdit->text() != verificationCode)
    {
        QMessageBox::warning(
            this,
            "Verification Code",
            "Verification Code Is Not Correct."
            );
        ui->codeEdit->setText("");
        return;
    }

    // Show Profile Page
    hide();
    auto *window = static_cast<Window *> (parent());
    window->switchPage(new Profile);
    deleteLater();
}
