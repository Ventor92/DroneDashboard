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

WorkerThread::WorkerThread(QObject *parent)
    : QThread(parent), m_worker(nullptr), m_timer(nullptr)
{
    m_worker = new WorkerData();
}

WorkerThread::~WorkerThread()
{
    // Usuwamy obiekty stworzone w wątku
    delete m_worker;
    delete m_timer;
}

void WorkerThread::run()
{
    // Tworzymy obiekt Worker i QTimer w wątku roboczym
    // m_worker = new WorkerData();
    m_timer = new QTimer();

    // Połączenie QTimer::timeout z Worker::doWork
    connect(m_timer, &QTimer::timeout, m_worker, &WorkerData::doWork);

    // Ustawienie interwału pracy
    m_timer->start(2000);

    // Uruchamiamy event loop w wątku
    exec();

    // Po zakończeniu event loopu, timer i worker zostaną usunięte w destruktorze
}
