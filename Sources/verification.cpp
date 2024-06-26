#include <QMessageBox>
#include <QValidator>

#include "Headers/profile.h"
#include "Headers/verification.h"
#include "Headers/window.h"
#include "ui_verification.h"

Verification::Verification(QString &code, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Verification)
{
    ui->setupUi(this);
    ui->codeEdit->setValidator(new QIntValidator);
    verificationCode = code;

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
    if (ui->codeEdit->text() != verificationCode) {
        QMessageBox box;
        QMessageBox::warning(&box, "Verification Code", "Verification Code Is Not Correct.");
        ui->codeEdit->setText("");
        return;
    }

    // Show Profile Page
    Window::changePage(new Profile, parentWidget());
}
