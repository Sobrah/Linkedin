#include "Headers/comment.h"
#include "ui_viewcomment.h"
#include <Header>

ViewComment::ViewComment(int commentID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewComment)
    , account(new Account)
    , comment(new Comment)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        comment->setCommentID(commentID);
        comment->selectComment();

        account->setAccountID(comment->getSenderID());
        account->selectAccountBaseID();
    }).then([=] {
        ui->usernameLabel->setText(account->getUsername());
        ui->commentTextLabel->setText(comment->getContentText());
    });

    qDebug("View Comment Starts.");
}

ViewComment::~ViewComment()
{
    delete ui;
    delete account;
    delete comment;
    qDebug("View Comment Ends.");
}
