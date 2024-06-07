#include <QMessageBox>

#include "Headers/profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);

    // Submit Button Clicked
    connect(ui->submitButton, &QPushButton::clicked, this, &Profile::submitButtonClicked);

    // Company Button Clicked
    connect(ui->companyButton, &QPushButton::clicked, this, &Profile::companyButtonClicked);

    qDebug("Profile Starts.");
}

Profile::~Profile()
{
    delete ui;
    qDebug("Profile Ends.");
}

void Profile::submitButtonClicked()
{
    const QString firstName = ui->firstNameEdit->text();
    const QString lastName = ui->lastNameEdit->text();
    const QString phoneNumber = ui->phoneNumberEdit->text();
    QMessageBox box;

    // Check Fields
    if (firstName.length() < 3) {
        QMessageBox::warning(&box,
                             "First Name Length",
                             "First Name Should Be At Least 3 Characters.");
        return;
    }
    if (lastName.length() < 4) {
        QMessageBox::warning(&box, "Last Name Length", "Last Name Should Be At Least 4 Characters.");
        return;
    }
    if (phoneNumber.length() < 8) {
        QMessageBox::warning(&box,
                             "Phone Number Length",
                             "Phone Number Should Be At Least 8 Characters.");
        return;
    }

    parentWidget()->close();
}

void Profile::companyButtonClicked()
{
    static int formStatus = 0;
    const QString signs[2] = {"User", "Company"};
    const QString lines[2] = {"Company Name", "Last Name"};

    // Reset Fields
    ui->firstNameEdit->setText("");
    ui->lastNameEdit->setText("");
    ui->phoneNumberEdit->setText("");
    ui->skillCombo->setCurrentIndex(-1);

    // Change Account Parts
    ui->lastNameEdit->setPlaceholderText(lines[formStatus]);
    ui->companyButton->setText(signs[formStatus]);

    formStatus = (formStatus + 1) % 2;

    // Cange Form Parts
    if (formStatus) {
        ui->firstNameEdit->hide();
    } else {
        ui->firstNameEdit->show();
    }
}
