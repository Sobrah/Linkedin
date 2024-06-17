#include "ui_collection.h"
#include <Header>

Collection::Collection(int postID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Collection)
    , post(new Post(this))
{
    ui->setupUi(this);

    post->setPostID(postID);
    RUN(POOL, [=] { post->selectPost(); }).then(this, [=] {
        ui->contentLable->setText(post->getContentText());
    });
}

Collection::~Collection()
{
    delete ui;
}
