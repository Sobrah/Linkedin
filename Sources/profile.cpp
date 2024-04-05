#include "Headers/profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);
    qDebug() << "Profile Starts.";
}

Profile::~Profile()
{
    delete ui;
    qDebug() << "Profile Ends.";
}

void Profile::on_submitButton_clicked()
{
    hide();
    deleteLater();
    parentWidget()->deleteLater();
}
