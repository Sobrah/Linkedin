#include "Headers/viewpost.h"
#include "ui_viewpost.h"

ViewPost::ViewPost(int postID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewPost)
    , account(new Account)
    , post(new Post)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        post->setPostID(postID);
        post->selectPost();

        account->setAccountID(post->getSenderID());
        account->selectAccountBaseID();

        Comment comment;
        return comment.selectComments(post->getPostID());
    }).then(this, [=](QVector<int> comments) {
        ui->usernameLabel->setText(account->getUsername());
        ui->postContentLabel->setText(post->getContentText());

        foreach (auto comment, comments) {
            ui->commentSectionLayout->addWidget(new ViewComment(comment));
        }
    });

    connect(ui->sendCommentButton, &QPushButton::clicked, this, &ViewPost::sendCommentButtonClicked);

    qDebug("View Post Starts.");
}

ViewPost::~ViewPost()
{
    delete ui;
    delete account;
    delete post;
    qDebug("View Post Ends.");
}

void ViewPost::sendCommentButtonClicked()
{
    RUN(POOL, [=] {
        Comment comment;
        comment.setContentText(ui->commentTextEdit->text());
        comment.setPostID(post->getPostID());
        comment.insertComment();
    }).then(this, [=] { ui->commentTextEdit->clear(); });
}
