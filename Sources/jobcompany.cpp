#include "ui_jobcompany.h"
#include <Header>

JobCompany::JobCompany(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JobCompany)
{
    ui->setupUi(this);
    ui->jobsScrollContents->layout()->addWidget(new JobCandidate);

    connect(ui->createJobButton, &QPushButton::clicked, this, &JobCompany::createJobButtonClicked);

    qDebug("Job Company Starts.");
}

JobCompany::~JobCompany()
{
    delete ui;
    qDebug("Job Company Ends.");
}

void JobCompany::createJobButtonClicked()
{
    Job newJob;
    newJob.setTitle(ui->jobTitleEdit->text());
    newJob.setSkill(ui->skillCombo->currentText());
    newJob.setWorkplaceType(ui->workplaceCombo->currentText());
    newJob.setLocation(ui->jobLocationEdit->text());
    newJob.setType(ui->jobTypeCombo->currentText());

    RUN(POOL, [&] { newJob.insertInformation(); }).then(FRAME, [=] {
        // Reset Fields
        ui->jobTitleEdit->setText("");
        ui->skillCombo->setCurrentIndex(-1);
        ui->workplaceCombo->setCurrentIndex(-1);
        ui->jobLocationEdit->setText("");
        ui->jobTypeCombo->setCurrentIndex(-1);
    });
}
