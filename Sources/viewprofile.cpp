#include <Views>

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

        Post post;
        return post.selectAccountPosts(accountID);
    }).then(this, [=](QVector<int> posts) {
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

        foreach (auto postID, posts) {
            ui->postContentsLayout->addWidget(new Collection(postID, parentWidget()));
        }
    });

    qDebug("View Profile Ends.");
}

ViewProfile::~ViewProfile()
{
    delete ui;
    delete account;
    qDebug("View Profile Ends.");
}
