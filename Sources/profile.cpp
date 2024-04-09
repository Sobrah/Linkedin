#include <QMessageBox>

#include "Headers/profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Profile)
{
    ui->setupUi(this);

    // Submit Button Clicked
    connect(ui->submitButton, &QPushButton::clicked, this, &Profile::submitButtonClicked);

    qDebug() << "Profile Starts.";
}

Profile::~Profile()
{
    delete ui;
    qDebug() << "Profile Ends.";
}

void Profile::submitButtonClicked()
{
    const QString jobTitle = ui->jobTitleEdit->text();
    const QString company = ui->companyEdit->text();
    const QString jobType = ui->jobTypeEdit->text();
    const QString university = ui->universityEdit->text();
    QMessageBox box;

    // Check Fields
    if (jobTitle.length() < 4) {
        QMessageBox::warning(&box, "Job Title Length", "Job Title Should Be At Least 4 Characters.");
        return;
    }
    if (company.length() < 4) {
        QMessageBox::warning(&box, "Company Length", "Company Should Be At Least 4 Characters.");
        return;
    }
    if (jobType.length() < 4) {
        QMessageBox::warning(&box, "Job Type Length", "Job Type Should Be At Least 4 Characters.");
        return;
    }
    if (university.length() < 4) {
        QMessageBox::warning(&box,
                             "University Length",
                             "University Should Be At Least 4 Characters.");
        return;
    }

    parentWidget()->close();
}
