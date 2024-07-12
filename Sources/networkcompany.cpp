#include <QLabel>
#include <Logics>
#include <Views>

NetworkCompany::NetworkCompany(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkCompany)
{
    ui->setupUi(this);

    POOL->start([=] { selectConnections(); });

    connect(this, &NetworkCompany::addConnection, this, [=](const QString &username) {
        layout()->addWidget(new QLabel(username));
    });

    qDebug("Network Company Starts.");
}

NetworkCompany::~NetworkCompany()
{
    delete ui;
    qDebug("Network Company ends.");
}

void NetworkCompany::selectConnections()
{
    QSqlQuery query;
    query.prepare("SELECT username FROM accounts WHERE accountID IN "
                  "(SELECT followerID FROM connections WHERE followingID = ?)");
    query.addBindValue(ACCOUNT->getAccountID());
    query.exec();
    while (query.next()) {
        emit addConnection(query.value("username").toString());
    }
}
