#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTextStream>

#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);

public slots:
    void newConnectionDetected();
    void startListinng();
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);
    void displayMessage(const QString& str);

    void processData(const int id, const QString &text);

signals:
    void newMessage(QString);

private:
    void appendToSocketList(QTcpSocket* socket);

    QTcpServer *ptrServer;
    QSet<QTcpSocket*> connection_set;

    QThread mThread;
};

#endif // TCPSERVER_H
