#include <QCoreApplication>
#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    : QObject{parent}
{
    ptrServer = new QTcpServer();

    if(ptrServer->listen(QHostAddress::LocalHost, 8080))
    {
        connect(&mThread, SIGNAL(started()), this, SLOT(startListinng()));
        connect(this, &TcpServer::newMessage, this, &TcpServer::displayMessage);
        connect(ptrServer, &QTcpServer::newConnection, this, &TcpServer::newConnectionDetected);
        // connect(this, &TcpServer::newMessage, this, &TcpServer::displayMessage);
        // connect(ptrServer, SIGNAL(newConnection()), this, SLOT(newConnectionDetected()));
        displayMessage(QString("INFO :: Server is listening..."));
    }
    else
    {
        // QMessageBox::critical(this,"QTCPServer",QString("Unable to start the server: %1.").arg(m_server->errorString()));
        displayMessage(QString("ERROR :: Unable to start the server: %1.").arg(ptrServer->errorString()));
        // exit(EXIT_FAILURE);
    }


    if (QThread::currentThread() == QCoreApplication::instance()->thread()) {
        qDebug() << "Jesteśmy w głównym wątku!";
    } else {
        qDebug() << "Jesteśmy w innym wątku!";
    }
}

void TcpServer::displayMessage(const QString& str)
{
    qDebug() << str;
}

void TcpServer::processData(const int id, const QString &text)
{
    displayMessage(QString("INFO :: próba wysłania %1 %2").arg(id).arg(text));
}

void TcpServer::newConnectionDetected()
{
    while (ptrServer->hasPendingConnections())
        appendToSocketList(ptrServer->nextPendingConnection());
}

void TcpServer::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &TcpServer::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &TcpServer::displayError);
    // ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));
    displayMessage(QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor()));
}

void TcpServer::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if (QThread::currentThread() == QCoreApplication::instance()->thread()) {
        qDebug() << "Jesteśmy w głównym wątku!";
    } else {
        qDebug() << "Jesteśmy w innym wątku!";
    }

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        emit newMessage(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);

    // if(fileType=="attachment"){
    //     QString fileName = header.split(",")[1].split(":")[1];
    //     QString ext = fileName.split(".")[1];
    //     QString size = header.split(",")[2].split(":")[1].split(";")[0];

    //     if (QMessageBox::Yes == QMessageBox::question(this, "QTCPServer", QString("You are receiving an attachment from sd:%1 of size: %2 bytes, called %3. Do you want to accept it?").arg(socket->socketDescriptor()).arg(size).arg(fileName)))
    //     {
    //         QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+fileName, QString("File (*.%1)").arg(ext));

    //         QFile file(filePath);
    //         if(file.open(QIODevice::WriteOnly)){
    //             file.write(buffer);
    //             QString message = QString("INFO :: Attachment from sd:%1 successfully stored on disk under the path %2").arg(socket->socketDescriptor()).arg(QString(filePath));
    //             emit newMessage(message);
    //         }else
    //             QMessageBox::critical(this,"QTCPServer", "An error occurred while trying to write the attachment.");
    //     }else{
    //         QString message = QString("INFO :: Attachment from sd:%1 discarded").arg(socket->socketDescriptor());
    //         emit newMessage(message);
    //     }
    // }else if(fileType=="message"){
    //     QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
    //     emit newMessage(message);
    // }

    if(fileType=="message")
    {
        QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        emit newMessage(message);
    }
}

void TcpServer::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
    if (it != connection_set.end()){
        displayMessage(QString("INFO :: A client has just left the room").arg(socket->socketDescriptor()));
        connection_set.remove(*it);
    }
    // refreshComboBox();

    socket->deleteLater();
}

void TcpServer::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        // QMessageBox::information(this, "QTCPServer", "The host was not found. Please check the host name and port settings.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        // QMessageBox::information(this, "QTCPServer", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
    default:
        // QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
        // QMessageBox::information(this, "QTCPServer", QString("The following error occurred: %1.").arg(socket->errorString()));
        break;
    }
}


void TcpServer::startListinng()
{
    qDebug() << "Server is listening...";
}
