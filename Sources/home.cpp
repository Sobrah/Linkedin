#include <QScrollBar>
#include <Logics>
#include <Views>

#include "headers/account.h"

Home::Home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    // Load More Posts
    connect(ui->loadMorePostsButton, &QPushButton::clicked, this, [=] {
        RUN(POOL, [=] {
            Post feed;

            // Select Feed
            return feed.selectFeed(feedLimit, feedOffset);
        }).then(this, [=](QVector<int> postsID) {
            foreach (auto postID, postsID) {
                ui->postContentsLayout->insertWidget(feedOffset++,
                                                     new Collection(postID, ui->containerGroup));
            }
        });
    });

    // First Feed Load
    ui->loadMorePostsButton->click();

    // Search Username
    connect(ui->searchCombo, &QComboBox::editTextChanged, this, [=](const QString &text) {
        POOL->start([=] { searchCurrentTextChanged(text); });
    });

    // Search Account View Profile
    connect(ui->searchCombo,
            &QComboBox::currentIndexChanged,
            this,
            &Home::searchCurrentIndexChanged);

    // Send Post
    connect(ui->postButton, &QPushButton::clicked, this, &Home::postButtonClicked);

    // Switch Home Page
    connect(ui->homeButton, &QPushButton::clicked, this, [=] { changePage(new Home, FRAME); });

    // Switch Network Page
    connect(ui->networkButton, &QPushButton::clicked, this, [=] {
        if (ACCOUNT->getIsCompany())
            changePage(new NetworkCompany, ui->containerGroup);
        else
            changePage(new NetworkPerson, ui->containerGroup);
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
    RUN(POOL, [&] {
        Post post;
        post.setContentText(ui->postTextEdit->toPlainText());
        post.insertPost();
    }).then(this, [=] { ui->postTextEdit->setPlainText(""); });
}

void Home::searchCurrentTextChanged(const QString &text)
{
    // Ignore Empty Request
    if (text.isEmpty()) {
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT username FROM accounts WHERE username LIKE ? ORDER BY username LIMIT 5");
    query.addBindValue(text + '%');
    query.exec();

    // Clear Items
    ui->searchCombo->clear();

    while (query.next()) {
        ui->searchCombo->addItem(query.value("username").toString());
    }
}

void Home::searchCurrentIndexChanged(int index)
{
    qDebug() << index;

    RUN(POOL, [=] {
        QString username = ui->searchCombo->currentText();
        return ACCOUNT->selectAccountIDBaseUsername(username);
    }).then(this, [=](int accountID) {
        changePage(new ViewProfile(accountID), ui->containerGroup);
    });
}
