#include "Headers/profile.h"
#include "ui_profile.h"

#include <QMessageBox>

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
    const QString jobtitle = ui->jobTitleEdit->text();
    const QString company = ui->companyEdit->text();
    const QString jobtype = ui->jobTypeEdit->text();
    const QString university = ui->universityEdit->text();

    if (jobtitle.length() == 0){
        QMessageBox::warning(
            this,
            "JobTitle Length",
            "Enter Your JobTitle .");
        return ;
    }
    if(company.length() == 0){
        QMessageBox::warning(
            this,
            "Company Length",
            "Enter Your Company .");
        return ;
    }
    if(jobtype.length() == 0){
        QMessageBox::warning(
            this,
            "JobType Length",
            "Enter Your JobType .");
        return ;
    }
    if(university.length() == 0){
        QMessageBox::warning(
            this,
            "University Length",
            "Enter Your University .");
        return ;
    }

    hide();
    deleteLater();
    parentWidget()->deleteLater();
}
