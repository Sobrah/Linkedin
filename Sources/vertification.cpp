#include "Headers/vertification.h"
#include "ui_vertification.h"

Vertification::Vertification(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Vertification)
{
    ui->setupUi(this);
}

Vertification::~Vertification()
{
    delete ui;
}
