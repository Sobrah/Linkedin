#include "Header"
#include "ui_networkcompany.h"

NetworkCompany::NetworkCompany(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkCompany)
{
    ui->setupUi(this);

    qDebug("Network Company Starts.");
}

NetworkCompany::~NetworkCompany()
{
    delete ui;
    qDebug("Network Company ends.");
}
