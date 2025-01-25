#include <QThread>
#include <QDebug>
#include <QCoreApplication>

#include "workerdata.h"
#include "tcpserver.h"

WorkerData::WorkerData(QObject *parent)
    : QObject(parent) {}

void WorkerData::doWork() {
    qDebug() << "Worker1 is working...";
    emit newData(1, "Message from Emitter");
}
