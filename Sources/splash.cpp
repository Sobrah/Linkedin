#include <Views>

Splash::Splash(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Splash)
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, [=] { changePage(new Login, FRAME); });

    qDebug("Splash Starts.");
}

Splash::~Splash()
{
    delete ui;
    qDebug("Splash Ends.");
}
