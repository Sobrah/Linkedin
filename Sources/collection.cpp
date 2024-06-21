#include "Headers/collection.h"
#include "ui_collection.h"
#include <Header>

Collection::Collection(int postID, QWidget *container, QWidget *parent)
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
        // Post Content

        // Adjust Content
        auto content = post->getContentText();
        content.truncate(25);
        content.append("...");
        ui->contentLable->setText(content);

        // Post Username
        ui->usernameLabel->setText(account->getUsername());

        // Suggested Tag
        if (hasConnection) {
            ui->tagLabel->hide();
        }

        // Reposted Tag
        if (!post->getIsReposted()) {
            ui->repostedLabel->hide();
        }

        // Repost Label
        auto repostCounter = ui->repostCounterLabel->text();
        repostCounter.prepend(QString::number(post->getRepostCounter()));
        ui->repostCounterLabel->setText(repostCounter);

        // Connection Status
        if (account->getIsCompany()) {
            ui->followButton->setText(followingStatus[hasConnection]);
        } else {
            ui->followButton->setText(connectionStatus[hasConnection]);
        }
    });

    // Follow Button Clicked
    connect(ui->followButton, &QPushButton::clicked, this, &Collection::followButtonClicked);

    // See More Button Clicked
    connect(ui->seeMoreButton, &QPushButton::clicked, this, [=] {
        changePage(new ViewPost(postID), container);
    });

    // Repost Button Clicked
    connect(ui->repostButton, &QPushButton::clicked, this, &Collection::repostButtonClicked);

    qDebug("Collection Starts.");
}

Collection::~Collection()
{
    delete ui;
    delete post;
    delete account;

    qDebug("Collection Ends.");
}

void Collection::followButtonClicked()
{
    RUN(POOL, [=] {
        if (hasConnection) {
            ACCOUNT->deleteConnection(account->getAccountID());
            hasConnection = false;
        } else {
            ACCOUNT->insertConnection(account->getAccountID());
            hasConnection = true;
        }
    }).then([=] {
        // Connection Status
        if (account->getIsCompany()) {
            ui->followButton->setText(followingStatus[hasConnection]);
        } else {
            ui->followButton->setText(connectionStatus[hasConnection]);
        }
    });
}

void Collection::repostButtonClicked()
{
    auto repost = [=] {
        Post repost;
        repost.setContentText(post->getContentText());
        repost.setIsReposted(true);

        repost.insertPost();

        // Increment Repost Counter
        post->updateRepost();
    };

    POOL->start(repost);
}
