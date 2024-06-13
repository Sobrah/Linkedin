#include <QVBoxLayout>

#include "Headers/jobperson.h"
#include "Headers/jobposition.h"
#include "Headers/utility.h"
#include "ui_jobperson.h"

JobPerson::JobPerson(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JobPerson)
{
    ui->setupUi(this);
    ui->skillLabel->setText(ACCOUNT->getSkill());

    ui->jobsScrollContents->layout()->addWidget(new JobPosition(0));
}

JobPerson::~JobPerson()
{
    delete ui;
}
