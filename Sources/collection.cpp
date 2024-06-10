#include "Headers/collection.h"
#include "ui_collection.h"

Collection::Collection(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Collection)
{
    ui->setupUi(this);
}

Collection::~Collection()
{
    delete ui;
}
