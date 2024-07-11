#include "Headers/collection.h"
#include <QMessageBox>
#include "ui_collection.h"
#include <Header>

Collection::Collection(int postID, QWidget *container, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Collection)
    , post(new Post)
    , account(new Account)
{
    ui->setupUi(this);

    // View Profile Button Clicked
    connect(ui->viewProfileButton,
            &QPushButton::clicked,
            this,
            &Collection::viewProfileButtonClicked);
    RUN(POOL, [=] {
        // Post Information
        post->setPostID(postID);
        post->selectPost();

        // Account Information
        int senderID = post->getSenderID();
        account->setAccountID(senderID);
        account->selectAccountBaseID();

        // Like Status
        hasLike = like->selectHasLike(post->getPostID());

        // Suggested Tag
        hasConnection = ACCOUNT->selectHasConnection(senderID);
    }).then(this, [=] {
        // Post Content

        // Adjust Content
        auto content = post->getContentText();
        if (content.length() > 25) {
            content.truncate(25);
            content.append("...");
        }
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
        ui->repostCounterLabel->setText(QString::number(post->getRepostCounter()));

        // Connection Status
        if (account->getIsCompany()) {
            ui->followButton->setText(followingStatus[hasConnection]);
        } else {
            ui->followButton->setText(connectionStatus[hasConnection]);
        }

        // Like Status
        ui->likeButton->setText(likeStatus[hasLike]);
    });

    // Follow Button Clicked
    connect(ui->followButton, &QPushButton::clicked, this, &Collection::followButtonClicked);

    // See More Button Clicked
    connect(ui->seeMoreButton, &QPushButton::clicked, this, [=] {
        changePage(new ViewPost(postID), container);
    });

    // Repost Button Clicked
    connect(ui->repostButton, &QPushButton::clicked, this, &Collection::repostButtonClicked);

    // Like Button Clicked
    connect(ui->likeButton, &QPushButton::clicked, this, &Collection::likeButtonClicked);

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
            return;
        }

        if (account->getIsCompany()) {
            ACCOUNT->insertConnection(account->getAccountID());
            hasConnection = true;
        }

        else {
            ACCOUNT->insertConnectionRequest(account->getAccountID());
        }
    }).then(this, [=] {
        // Connection Status
        if (account->getIsCompany()) {
            ui->followButton->setText(followingStatus[hasConnection]);
        } else {
            QMessageBox::warning(this, "Connection Request", "Connection Is Sent.");
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

        auto counter = ui->repostCounterLabel->text().toInt();
        ui->repostCounterLabel->setText(QString::number(counter + 1));
    };

    POOL->start(repost);
}

void Collection::likeButtonClicked()
{
    RUN(POOL, [=] {
        if (hasLike) {
            like->deleteLike(post->getPostID());
            hasLike = false;
        } else {
            like->insertLike(post->getPostID());
            hasLike = true;
        }
    }).then([=] {
        // Like Status
        ui->likeButton->setText(likeStatus[hasLike]);
    });
}

void Collection::viewProfileButtonClicked()
{
    int accountID = account->getAccountID();
    changePage(new ViewProfile(accountID), FRAME);
}
