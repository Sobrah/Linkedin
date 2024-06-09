#ifndef UTILITY_H
#define UTILITY_H

#include <QThreadPool>
#include <QtConcurrentRun>

#define RUN QtConcurrent::run

extern int ACCOUNT_ID;
extern bool IS_COMPANY;
extern QThreadPool *POOL;

void initializeDatabase();
bool checkSession();
void changePage(QWidget *, QWidget *);
void decideInitialPage(QWidget *);
QString generateCode(int = 4);

#endif // UTILITY_H
