#ifndef CLIENGINE_H
#define CLIENGINE_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTextStream>

class CliEngine : public QObject
{
    Q_OBJECT
public:
    explicit CliEngine(QObject *parent = nullptr);

signals:
    void onReadLine(QString line);

public slots:
    void readStdInput();
    void handleStdInput(QString line);
    void writeStdOutput(QString line);

private:
    QThread mThread;
    std::atomic<bool> mIsStop;
};

#endif // CLIENGINE_H
