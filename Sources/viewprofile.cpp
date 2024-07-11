#include "Headers/viewprofile.h"
#include <QSqlQuery>
#include "ui_viewprofile.h"
#include <Headers/utility.h>

ViewProfile::ViewProfile(int accountID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewProfile)
    , account(new Account)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        // Account Information
        account->setAccountID(accountID);
        account->selectAccountBaseID();
    }).then(this, [=] {
        if (account->getIsCompany()) {
            // Company Name
            ui->nameTitleLabel->setText("Company Name");
            ui->nameLable->setText(account->getFirstName());

            // Phone Number
            ui->lastNameTitleLabel->setText("Phone Number");
            ui->lastNameLabel->setText(account->getPhoneNumber());
        } else {
            // First Name
            ui->nameLable->setText(account->getFirstName());

            // Last Name
            ui->lastNameLabel->setText(account->getLastName());
        }

        // Email
        ui->emailLabel->setText(account->getEmail());

        // Skill
        ui->skillLabel->setText(account->getSkill());
    });

    qDebug("View Profile Starts.");
}

ViewProfile::~ViewProfile()
{
    delete ui;
    qDebug("View Profile Ends.");
}
