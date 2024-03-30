#include "Headers/verification.h"
#include "Headers/profile.h"

#include "ui_verification.h"

Verification::Verification(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Verification)
{
    ui->setupUi(this);
}

Verification::~Verification()
{
    delete ui;
}

void Verification::on_confirmButton_clicked()
{
    Profile *w = new Profile;
    w->show();

    close();
}