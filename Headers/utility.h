#ifndef UTILITY_H
#define UTILITY_H

#include <QSqlQuery>
#include <QThreadPool>
#include <QtConcurrentRun>
#include <Header>

#define RUN QtConcurrent::run

extern QWidget *FRAME;
extern Account *ACCOUNT;
extern QThreadPool *POOL;

void initializeDatabase();
bool checkSession();
void changePage(QWidget *, QWidget *);
void decideInitialPage();
bool executeQuery(QSqlQuery &, const QString &, const QVariantList &);
QString captchaCode(int = 4);

#endif // UTILITY_H
