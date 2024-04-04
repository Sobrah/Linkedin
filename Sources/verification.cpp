#include "Headers/verification.h"
#include "Headers/profile.h"

#include "ui_verification.h"

#include <QMessageBox>
#include <QValidator>

int randomNumber;

Verification::Verification(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Verification)
{
    ui->setupUi(this);
    int randNum = rand()%9000+1000;
    randomNumber = randNum;
    ui->codeLine->setValidator(new QIntValidator);
    QMessageBox::information(this,"Captcha","Your captcha code is " + QString::number(randNum) + " .");
}

Verification::~Verification()
{
    delete ui;
}

void Verification::on_confirmButton_clicked()
{

    QString codeText = QString::number(randomNumber);
    if(ui->codeLine->text() != codeText){
        randomNumber = rand()%9000+1000;
        QMessageBox::warning(this,"Eror!","The number was incorrect , the new captcha is " + QString::number(randomNumber) + " .");
        ui->codeLine->setText("");
    }
    else {
        Profile *w = new Profile;
        w->show();

        close();
    }
}
