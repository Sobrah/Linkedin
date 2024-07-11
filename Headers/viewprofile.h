#ifndef VIEWPROFILE_H
#define VIEWPROFILE_H

#include <QWidget>
#include <Headers/account.h>

namespace Ui {
class ViewProfile;
}

class ViewProfile : public QWidget
{
    Q_OBJECT

public:
    explicit ViewProfile(int, QWidget *parent = nullptr);
    ~ViewProfile();

private:
    Ui::ViewProfile *ui;

    Account *account;
};

#endif // VIEWPROFILE_H
