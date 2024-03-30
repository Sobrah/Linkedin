#include "Headers/vertification.h"
#include "Headers/profile.h"

#include "ui_vertification.h"

Vertification::Vertification(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Vertification)
{
    ui->setupUi(this);
}

Vertification::~Vertification()
{
    delete ui;
}

void Vertification::on_confirmButton_clicked()
{
    Profile *w = new Profile;
    w->show();

    close();
}