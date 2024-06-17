#include "ui_home.h"
#include <Header>

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    loadFeed();

    ui->setupUi(this);
    // ui->postGroup->layout()->addWidget(new Collection);

    // Send Post
    connect(ui->postButton, &QPushButton::clicked, this, &Home::postButtonClicked);

    // Search Username
    connect(ui->searchCombo, &QComboBox::currentTextChanged, this, [=](const QString &text) {
        POOL->start([=] { searchCurrentTextChanged(text); });
    });

    // Switch Home Page
    connect(ui->homeButton, &QPushButton::clicked, this, [=] { changePage(new Home, FRAME); });

    // Switch Network Page
    connect(ui->networkButton, &QPushButton::clicked, this, [=] {
        if (ACCOUNT->getIsCompany())
            changePage(new NetworkCompany, ui->containerGroup);
    });

    // Switch Job Page
    connect(ui->jobButton, &QPushButton::clicked, this, [=] {
        QWidget *page;

        if (ACCOUNT->getIsCompany())
            page = new JobCompany;
        else
            page = new JobPerson;

        changePage(page, ui->containerGroup);
    });

    // Switch Me Page
    connect(ui->userButton, &QPushButton::clicked, this, [=] {
        changePage(new Me, ui->containerGroup);
    });

    qDebug("Home Starts.");
}

Home::~Home()
{
    delete ui;
    qDebug("Home Ends.");
}

void Home::postButtonClicked()
{
    Post post;
    post.setContentText(ui->postTextEdit->toPlainText());
    RUN(POOL, [&] { post.insertPost(); }).then(this, [=] { ui->postTextEdit->setPlainText(""); });
}

void Home::searchCurrentTextChanged(const QString &text)
{
    QSqlQuery query;
    query.prepare("SELECT username FROM accounts WHERE username LIKE ? LIMIT 5");
    query.addBindValue(text + '%');
    query.exec();

    while (query.next()) {
        ui->searchCombo->addItem(query.value("username").toString());
    }
}

void Home::loadFeed()
{
    RUN(POOL, [=] {
        Post feed;
        return feed.selectFeed(feedLimit, feedOffset);
    }).then(this, [=](QVector<int> postsID) {
        foreach (auto postID, postsID) {
            ui->postContents->layout()->addWidget(new Collection(postID));
        }
    });

    // QVector<int> postsID;
    // RUN(POOL, [&] { postsID = feed.selectFeed(feedLimit, feedOffset); }).then(this, [&] {
    //     qDebug() << postsID.size();
    //     // ui->postGroup->layout()->addWidget(new Collection(postID));

    //     feedOffset += feedLimit;
    // });
}
