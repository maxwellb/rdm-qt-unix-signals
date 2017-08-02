#include <QCoreApplication>
#include <QDebug>
#include "sigwatch.h"

#if Q_OS_WIN
const int SIGINT = 2;
const int SIGTERM = 15;
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    qDebug() << "Hello from process" << QCoreApplication::applicationPid();

    UnixSignalWatcher sigwatch;
    sigwatch.watchForSignal(SIGINT);
    sigwatch.watchForSignal(SIGTERM);
    QObject::connect(&sigwatch, SIGNAL(unixSignal(int)), &app, SLOT(quit()));

    int exitcode = app.exec();
    qDebug() << "Goodbye";
    return exitcode;
}

