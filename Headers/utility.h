#ifndef UTILITY_H
#define UTILITY_H

#include <QThreadPool>
#include <QtConcurrentRun>

#include "Headers/account.h"

#define RUN QtConcurrent::run

extern QWidget *FRAME;
extern Account *ACCOUNT;
extern QThreadPool *POOL;

void initializeDatabase();
bool checkSession();
void changePage(QWidget *, QWidget *);
void decideInitialPage();
QString generateCode(int = 4);

#endif // UTILITY_H
