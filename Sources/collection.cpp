#include "Headers/collection.h"
#include "ui_collection.h"
#include <Header>

Collection::Collection(int postID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Collection)
    , post(new Post)
    , account(new Account)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        // Post Information
        post->setPostID(postID);
        post->selectPost();

        // Account Information
        int senderID = post->getSenderID();
        account->setAccountID(senderID);
        account->selectAccountBaseID();

        // Suggested Tag
        hasConnection = ACCOUNT->selectHasConnection(senderID);
        
    }).then(this, [=] {
        ui->contentLable->setText(post->getContentText());
        ui->usernameLabel->setText(account->getUsername());
        if (hasConnection) {
            ui->tagLabel->hide();
        }
    });

    qDebug("Collection Starts.");
}

Collection::~Collection()
{
    delete ui;
    delete post;
    delete account;

    qDebug("Collection Ends.");
}
