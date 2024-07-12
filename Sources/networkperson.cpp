#include <Logics>
#include <Views>

NetworkPerson::NetworkPerson(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkPerson)
{
    ui->setupUi(this);

    RUN(POOL, [=] {
        return ACCOUNT->selectConnectionRequests();
    }).then(this, [=](QVector<int> connectionRequests) {
        foreach (auto connectionRequest, connectionRequests) {
            ui->requestGroup->layout()->addWidget(new NetworkRequest(connectionRequest));
        }
    });

    RUN(POOL, [=] {
        return ACCOUNT->selectConnectionSuggestions(5);
    }).then(this, [=](QVector<int> suggestions) {
        foreach (auto suggestion, suggestions) {
            ui->suggestGroup->layout()->addWidget(new NetworkSuggestion(suggestion));
        }
    });

    qDebug("Network Person Starts.");
}

NetworkPerson::~NetworkPerson()
{
    delete ui;
    qDebug("Network Person Ends");
}
