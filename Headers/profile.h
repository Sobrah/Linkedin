#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

private:
    void submitButtonClicked();
    void switchButtonClicked();

    Ui::Profile *ui;
    bool formStatus = false;

signals:
    void warnMessage(QString, QString);
};

#endif // PROFILE_H
