#include <QFile>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QtConcurrentRun>

#include "Headers/home.h"
#include "Headers/splash.h"
#include "Headers/window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    // Configure Layout
    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Add Initial Page
    QtConcurrent::run(POOL, &Window::checkSession, this).then(this, [=](bool status) {
        if (status)
            changePage(new Home, this);
        else
            changePage(new Splash, this);
    });

    qDebug() << "Window Starts.";
}

Window::~Window()
{
    delete ui;
    qDebug() << "Window Ends.";
}

void Window::changePage(QWidget *page, QWidget *parent)
{
    auto children = parent->findChildren<QWidget *>();
    foreach (auto widget, children) {
        widget->hide();
        widget->deleteLater();
    }

    parent->layout()->addWidget(page);
    page->show();
}

bool Window::checkSession()
{
    QFile file("session");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (!file.exists())
        return false;

    QString username = file.readLine().trimmed();
    QString password = file.readLine().trimmed();
    file.close();

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);
    query.exec();

    // Invalid Credentials
    if (!query.first())
        return false;

    return true;
}
