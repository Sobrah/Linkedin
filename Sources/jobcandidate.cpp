#include "Headers/jobcandidate.h"
#include "ui_jobcandidate.h"
#include <Header>

JobCandidate::JobCandidate(int jobRequestID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JobCandidate)
    , account(new Account)
    , job(new Job)
    , jobRequestID(jobRequestID)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        auto accountID = job->selectAccountIDBaseJobRequestID(jobRequestID);
        account->setAccountID(accountID);
        account->selectAccountBaseID();

        auto jobID = job->selectJobIDBaseJobRequestID(jobRequestID);
        job->setJobID(jobID);
        job->selectJob();
    }).then(this, [=] {
        ui->usernameLabel->setText(account->getUsername());
        ui->jobTitleLabel->setText(job->getTitle());
    });

    connect(ui->acceptButton, &QPushButton::clicked, this, &JobCandidate::acceptButtonClicked);

    connect(ui->ignoreButton, &QPushButton::clicked, this, &JobCandidate::rejectButtonClicked);

    qDebug("Job Candidate Starts.");
}

JobCandidate::~JobCandidate()
{
    delete ui;
    delete account;
    delete job;
    qDebug("Job Candidate Ends.");
}

void JobCandidate::acceptButtonClicked()
{
    RUN(POOL, [=] { job->updateJobsRequestsIsAccepted(jobRequestID); }).then(this, [=] {
        deleteLater();
    });
}

void JobCandidate::rejectButtonClicked()
{
    RUN(POOL, [=] { job->deleteJobsRequests(jobRequestID); }).then(this, [=] { deleteLater(); });
}
