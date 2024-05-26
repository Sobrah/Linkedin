#include <QtConcurrentRun>

#include "Headers/home.h"
#include "Headers/post.h"
#include "Headers/window.h"
#include "ui_home.h"

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    connect(ui->postButton, &QPushButton::clicked, this, &Home::postButtonClicked);

    qDebug() << "Home Starts.";
}

Home::~Home()
{
    delete ui;
    qDebug() << "Home Ends.";
}

void Home::postButtonClicked()
{
    POOL->start([&] { Post(ui->postTextEdit->toPlainText()); });
}
