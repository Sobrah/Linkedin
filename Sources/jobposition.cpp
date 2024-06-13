#include "Headers/jobposition.h"
#include "Headers/job.h"
#include "Headers/utility.h"
#include "ui_jobposition.h"

JobPosition::JobPosition(int row, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JobPosition)
    , row(row)
{
    ui->setupUi(this);

    POOL->start([=] { getInformation(); });

    connect(ui->statusButton, &QPushButton::clicked, this, [=] {
        POOL->start([=] { statusButtonClicked(); });
    });
}

JobPosition::~JobPosition()
{
    delete ui;
}

void JobPosition::getInformation()
{
    job = new Job(ACCOUNT->getSkill(), row);

    if (!job->getJobID()) {
        row = false;
        return;
    }

    ui->titleLabel->setText(job->getTitle());
    ui->companyNameLabel->setText(job->getCompanyName());
    ui->companyLocationLabel->setText(job->getLocation());
    ui->workplaceTypeLabel->setText(job->getWorkplaceType());

    if (job->hasRequested()) {
        ui->statusButton->setText("Pending");
    }

    if (job->isAccepted()) {
        ui->statusButton->setText("You Are Accepted");
        ui->statusButton->setEnabled(false);
    }
}

void JobPosition::statusButtonClicked()
{
    if (ui->statusButton->text() == "Apply") {
        job->applyRequest();
        ui->statusButton->setText("Pending");

    } else {
        job->removeRequest();
        ui->statusButton->setText("Apply");
    }
}
