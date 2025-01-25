#ifndef WORKERDATA_H
#define WORKERDATA_H

#include <QObject>
#include <QString>
#include <QDebug>

class WorkerData : public QObject {
    Q_OBJECT
public:
    explicit WorkerData(QObject *parent = nullptr);

public slots:
    void doWork();

signals:
    void newData(const int id, const QString &text);
};

#endif // WORKERDATA_H
