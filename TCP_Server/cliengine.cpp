#include <QDebug>

#include "cliengine.h"
// #include "linenoise.h"

CliEngine::CliEngine(QObject *parent)
    : QObject{parent}
{
    this->moveToThread(&mThread);
    connect(&mThread, SIGNAL(started()), this, SLOT(readStdInput()));
    connect(this, SIGNAL(onReadLine(QString)), this, SLOT(handleStdInput(QString)));

    mIsStop = false;
    mThread.start();
}

void CliEngine::readStdInput()
{
    QTextStream stream(stdin);
    while (!mIsStop)
    {
        QString line = stream.readLine();
        emit onReadLine(line);
    }
}

void CliEngine::handleStdInput(QString line)
{
    if(line == "exit")
    {
        qDebug() << line;
    }
    else
    {
        qDebug() << "Unknow command: " <<  line;
    }
}

void CliEngine::writeStdOutput(QString line)
{
    QTextStream stream(stdout);
}

// void CliEngine::stop()
// {
//     mStop = true;
//     mStream.device()->close();
// }
