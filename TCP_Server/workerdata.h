#ifndef WORKERDATA_H
#define WORKERDATA_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QTimer>

class WorkerData : public QObject {
    Q_OBJECT
public:
    explicit WorkerData(QObject *parent = nullptr);

public slots:
    void doWork();

signals:
    void newData(const int id, const QString &text);
};


class WorkerThread : public QThread
{
    Q_OBJECT

public:
    explicit WorkerThread(QObject *parent = nullptr);
    ~WorkerThread() override;
    WorkerData *m_worker; // Wskaźnik na obiekt Worker
    QTimer *m_timer;  // Timer do cyklicznego wywoływania pracy

protected:
    void run() override;

private:
};

#endif // WORKERDATA_H
