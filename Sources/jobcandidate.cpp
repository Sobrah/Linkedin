#include <QSqlQuery>

#include "Headers/jobcandidate.h"
#include "ui_jobcandidate.h"

JobCandidate::JobCandidate(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JobCandidate)
{
    ui->setupUi(this);
}

JobCandidate::~JobCandidate()
{
    delete ui;
}

void JobCandidate::getInformation()
{
    // QSqlQuery
}
