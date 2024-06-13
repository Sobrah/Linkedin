#ifndef VIEWPROFILE_H
#define VIEWPROFILE_H

#include <QWidget>

namespace Ui {
class ViewProfile;
}

class ViewProfile : public QWidget
{
    Q_OBJECT

public:
    explicit ViewProfile(QWidget *parent = nullptr);
    ~ViewProfile();

private:
    Ui::ViewProfile *ui;
};

#endif // VIEWPROFILE_H
