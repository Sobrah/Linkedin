#ifndef HOME_H
#define HOME_H

#include <QWidget>

namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private:
    void postButtonClicked();
    void searchCurrentTextChanged(const QString &);
    void loadFeed();

    Ui::Home *ui;
    int feedLimit = 10;
    int feedOffset = false;
};

#endif // HOME_H
