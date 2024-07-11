#include "Headers/window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    qDebug("Window Starts.");
}

Window::~Window()
{
    delete ui;
    qDebug("Window Ends.");
}

void Window::closeEvent(QCloseEvent *)
{
    deleteLater();
}
