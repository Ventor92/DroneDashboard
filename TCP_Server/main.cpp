#include <QCoreApplication>
#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

#include <QThread>
#include <QTextStream>
// #include <iostream>

#include <QDebug>

#include "cliengine.h"
#include "tcpserver.h"

static QTcpServer* m_server;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CliEngine cliEngine;
    TcpServer tcpServer;

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    qDebug() << "Application started. Type 'exit' to quit.";
    return a.exec();
}


// #include "main.moc"
// "main.moc" depends on the declaration of Object above!
