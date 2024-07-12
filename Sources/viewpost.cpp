#include <Views>

ViewPost::ViewPost(int postID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewPost)
    , account(new Account)
    , post(new Post)
{
    ui->setupUi(this);

    RUN(POOL,
        // Load Account
        [=] {
            post->setPostID(postID);
            post->selectPost();

            account->setAccountID(post->getSenderID());
            account->selectAccountBaseID();
        })
        // Account UI
        .then(this,
              [=] {
                  ui->usernameLabel->setText(account->getUsername());
                  ui->postContentLabel->setText(post->getContentText());
              })
        // Load Comments
        .then(POOL,
              [=] {
                  Comment comment;
                  return comment.selectComments(post->getPostID());
              })
        // Comment UI
        .then(this,
              [=](QVector<int> comments) {
                  foreach (auto comment, comments) {
                      ui->commentSectionLayout->addWidget(new ViewComment(comment));
                  }
              })
        // Load Likes
        .then(POOL,
              [=] {
                  Like like;
                  return like.selectLikesBasePost(post->getPostID());
              })
        // Like UI
        .then(this, [=](QVector<int> accountIDs) {
            foreach (auto accountID, accountIDs) {
                ui->likeSectionLayout->addWidget(new ViewLike(accountID));
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

        return comment.getCommentID();
    }).then(this, [=](int commentID) {
        ui->commentTextEdit->clear();
        ui->commentSectionLayout->insertWidget(2, new ViewComment(commentID));
    });
}
