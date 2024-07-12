#include <Logics>
#include <Views>

JobPosition::JobPosition(int index, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JobPosition)
    , job(new Job)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        job->selectInformation(index);
        job->selectRequest();
    }).then(this, [=] { setInformation(); });

    connect(ui->statusButton, &QPushButton::clicked, this, [=] {
        POOL->start([=] { statusButtonClicked(); });
    });

    qDebug("Job Position Starts.");
}

JobPosition::~JobPosition()
{
    delete ui;
    delete job;
    qDebug("Job Position Ends.");
}

void JobPosition::setInformation()
{
    if (!job->getJobID()) {
        return;
    }

    // Set Information
    ui->titleLabel->setText(job->getTitle());
    ui->companyNameLabel->setText(job->getCompanyName());
    ui->companyLocationLabel->setText(job->getLocation());
    ui->workplaceTypeLabel->setText(job->getWorkplaceType());

    // Pending Status Button
    if (job->getIsRequested()) {
        ui->statusButton->setText("Pending");
    }

    // Accepted Status Button
    if (job->getIsAccepted()) {
        ui->statusButton->setEnabled(false);
        ui->statusButton->setText("You Are Accepted");
    }
}

void JobPosition::statusButtonClicked()
{
    if (ui->statusButton->text() == "Apply") {
        job->insertRequest();
        ui->statusButton->setText("Pending");

    } else {
        job->deleteRequest();
        ui->statusButton->setText("Apply");
    }
}
