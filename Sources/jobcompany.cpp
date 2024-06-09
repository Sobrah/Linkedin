#include "Headers/jobcompany.h"
#include "Headers/job.h"
#include "Headers/utility.h"
#include "ui_jobcompany.h"

JobCompany::JobCompany(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JobCompany)
{
    ui->setupUi(this);

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
    POOL->start([&] {
        Job(ui->jobTitleEdit->text(),
            ui->workplaceCombo->currentText(),
            ui->jobLocationEdit->text(),
            ui->jobTypeCombo->currentText());
    });
}
