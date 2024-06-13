#include "Headers/viewprofile.h"
#include "ui_viewprofile.h"

ViewProfile::ViewProfile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewProfile)
{
    ui->setupUi(this);
}

ViewProfile::~ViewProfile()
{
    delete ui;
}
