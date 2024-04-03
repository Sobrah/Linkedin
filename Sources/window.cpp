#include <QHBoxLayout>

#include "Headers/window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    auto *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    qDebug() << "Window Starts.";
}

Window::~Window()
{
    delete ui;
    qDebug() << "Window Ends.";
}

void Window::switchPage(QWidget *page)
{
    layout()->addWidget(page);
    page->show();
}
