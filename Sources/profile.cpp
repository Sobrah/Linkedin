#include <QIntValidator>
#include <QMessageBox>
#include <QSqlQuery>

#include "Headers/company.h"
#include "Headers/person.h"
#include "Headers/profile.h"
#include "Headers/utility.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);
    ui->phoneNumberEdit->setValidator(new QIntValidator);

    // Warn Message Emitted
    connect(this, &Profile::warnMessage, this, [=](QString title, QString text) {
        QMessageBox box;
        QMessageBox::warning(&box, title, text);
    });

    // Submit Button Clicked
    connect(ui->submitButton, &QPushButton::clicked, this, [=] {
        POOL->start([=] { submitButtonClicked(); });
    });

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
    const QString skill = ui->skillCombo->currentText();

    // Check Fields
    if (firstName.length() < 4) {
        if (formStatus) {
            emit warnMessage("Company Name Length", "Company Name Should Be At Least 4 Characters.");
            return;
        }
        emit warnMessage("First Name Length", "First Name Should Be At Least 4 Characters.");
        return;
    }
    if (!formStatus) {
        if (lastName.length() < 4) {
            emit warnMessage("Last Name Length", "Last Name Should Be At Least 4 Characters.");
            return;
        }
    }
    if (phoneNumber.length() < 4) {
        emit warnMessage("Phone Number Length", "Phone Number Should Be At Least 4 Characters.");
        return;
    }
    if (skill == "") {
        emit warnMessage("Skill Selection", "You Should Choose A Skill.");
        return;
    }

    ACCOUNT->setPhoneNumber(phoneNumber);
    ACCOUNT->setSkill(skill);

    POOL->start([=] {
        if (formStatus) {
            Company(ACCOUNT, firstName);
        } else {
            Person(ACCOUNT, firstName, lastName);
        }

    });

    decideInitialPage();
}

void Profile::companyButtonClicked()
{
    const QString signs[2] = {"User", "Company"};
    const QString placeHolders[2] = {"Company Name", "First Name"};

    // Reset Fields
    ui->firstNameEdit->setText("");
    ui->lastNameEdit->setText("");
    ui->phoneNumberEdit->setText("");
    ui->skillCombo->setCurrentIndex(-1);

    // Change Account Parts
    ui->firstNameEdit->setPlaceholderText(placeHolders[formStatus]);
    ui->companyButton->setText(signs[formStatus]);

    formStatus = (formStatus + 1) % 2;

    // Change Form Parts
    if (formStatus) {
        ui->lastNameEdit->hide();
    } else {
        ui->lastNameEdit->show();
    }
}
