#include "Headers/viewpost.h"
#include "ui_viewpost.h"

ViewPost::ViewPost(int, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewPost)
{
    ui->setupUi(this);
}

ViewPost::~ViewPost()
{
    delete ui;
}
