#include <QVBoxLayout>
#include <Logics>
#include <Views>

JobPerson::JobPerson(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JobPerson)
{
    ui->setupUi(this);
    ui->skillLabel->setText(ACCOUNT->getSkill());

    RUN(POOL, [=] { jobsNumber = Job().selectJobsNumber(); }).then(FRAME, [=] {
        // First Jobs Maximum
        int maximum = 5;
        if (jobsNumber < maximum) {
            maximum = jobsNumber;
        }

        for (; index < maximum; index++) {
            ui->jobsScrollContents->layout()->addWidget(new JobPosition(index));
        }
    });

    // Show All Jobs
    connect(ui->showAllButton, &QPushButton::clicked, this, [=] {
        for (; index < jobsNumber; index++) {
            ui->jobsScrollContents->layout()->addWidget(new JobPosition(index));
        }
    });

    qDebug("Job Person Starts.");
}

JobPerson::~JobPerson()
{
    delete ui;
    qDebug("Job Person Ends.");
}
