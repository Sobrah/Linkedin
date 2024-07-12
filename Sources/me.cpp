#include <QStyleFactory>
#include <Views>

Me::Me(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Me)
{
    ui->setupUi(this);

    // Initialize Information
    ui->firstNameLabel->setText(ACCOUNT->getFirstName());
    ui->lastNameLabel->setText(ACCOUNT->getLastName());
    ui->usernameLabel->setText(ACCOUNT->getLastName());
    ui->skillLabel->setText(ACCOUNT->getSkill());
    ui->biographyEdit->setText(ACCOUNT->getBiography());

    ui->styleCombo->addItems(QStyleFactory::keys());

    // Save Button Clicked
    connect(ui->saveButton, &QPushButton::clicked, this, [=] {
        POOL->start([=] { saveButtonClicked(); });
    });

    // Apply Style Button Clicked
    connect(ui->applyStyleButton, &QPushButton::clicked, this, [=] {
        QApplication::setStyle(QStyleFactory::create(ui->styleCombo->currentText()));
    });

    qDebug("Me Starts.");
}

Me::~Me()
{
    delete ui;
    qDebug("Me Ends.");
}

void Me::saveButtonClicked()
{
    const QString bio = ui->biographyEdit->text();
    QSqlQuery query;
    query.prepare("UPDATE accounts SET biography = ? WHERE accountID = ?");
    query.addBindValue(bio);
    query.addBindValue(ACCOUNT->getAccountID());
    query.exec();
}
