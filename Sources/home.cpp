#include <QSqlQuery>
#include <QtConcurrentRun>

#include "Headers/home.h"
#include "Headers/me.h"
#include "Headers/post.h"
#include "Headers/window.h"
#include "ui_home.h"

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    connect(ui->postButton, &QPushButton::clicked, this, &Home::postButtonClicked);
    connect(ui->searchCombo, &QComboBox::currentTextChanged, this, [=](const QString &text) {
        static_cast<void>(QtConcurrent::run(POOL, &Home::search_CurrentTextChanged, this, text));
    });
    connect(ui->userButton, &QPushButton::clicked, this, [=] {
        Window::changePage(new me, parentWidget());
    });
    qDebug() << "Home Starts.";
}

Home::~Home()
{
    delete ui;
    qDebug() << "Home Ends.";
}

void Home::postButtonClicked()
{
    POOL->start([&] { Post(ui->postTextEdit->toPlainText()); });
}

void Home::search_CurrentTextChanged(const QString &text)
{
    QSqlQuery Query;
    Query.prepare("SELECT username FROM users WHERE username LIKE ? LIMIT 5");
    Query.addBindValue(text + '%');
    Query.exec();
    while (Query.next()) {
        ui->searchCombo->addItem(Query.value("username").toString());
    }
}
