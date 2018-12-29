#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QtGlobal>
#include <stdio.h>

class thread : public QThread
{
    Q_OBJECT
public:
    thread();
    void run();


protected:

private:


};

#endif // THREAD_H
