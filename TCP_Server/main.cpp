#include <QCoreApplication>
#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

#include <QThread>
#include <QTextStream>
#include <QTimer>

#include <QDebug>

#include "cliengine.h"
#include "tcpserver.h"
#include "workerdata.h"

static QTcpServer* m_server;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CliEngine cliEngine;
    TcpServer tcpServer;

    WorkerThread threadWorkerData;
    // WorkerData workerData;

    // workerData.moveToThread(&threadWorkerData);

    threadWorkerData.start();
    // Połączenie sygnałów i slotów
    const WorkerData *const ptrWD = threadWorkerData.m_worker;

    QObject::connect(&threadWorkerData, &QThread::started, [&]() {
        QObject::connect(ptrWD, &WorkerData::newData, &tcpServer, &TcpServer::processData); // Interwał w milisekundach (1 sekunda)
    });

    // QTimer timer;
    // timer.moveToThread(&threadWorkerData);
    // QObject::connect(&timer, &QTimer::timeout, &workerData, &WorkerData::doWork);

    // QObject::connect(&threadWorkerData, &QThread::started, [&]() {
    //     timer.start(2000); // Interwał w milisekundach (1 sekunda)
    // });




    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.
    if (QThread::currentThread() == QCoreApplication::instance()->thread()) {
        qDebug() << "Jesteśmy w głównym wątku!";
    } else {
        qDebug() << "Jesteśmy w innym wątku!";
    }

    qDebug() << "Application started. Type 'exit' to quit.";
    return a.exec();
}


// #include "main.moc"
// "main.moc" depends on the declaration of Object above!
