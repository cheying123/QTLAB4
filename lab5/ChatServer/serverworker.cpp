#include "serverworker.h"
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>

ServerWorker::ServerWorker(QObject *parent) : QObject(parent)
{
    m_serverSocket = new QTcpSocket(this);
    connect(m_serverSocket, &QTcpSocket::readyRead,this,&ServerWorker::onReadyRead);
}

bool ServerWorker::setSockerDescriptor(qintptr sockerDescriptor)
{
    return m_serverSocket->setSocketDescriptor(sockerDescriptor);
}

void ServerWorker::onReadyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_5_12);

    for(;;){
        socketStream.startTransaction();
        socketStream >> jsonData;
        if( socketStream.commitTransaction() ){
            emit logMessage(QString::fromUtf8(jsonData));
            sendMessage("I recieved message");
        } else{
            break;
        }
    }
}

void ServerWorker::sendMessage(const QString &text, const QString &type)
{
    if(m_serverSocket->state() != QAbstractSocket::ConnectedState){
        return;
    }

    if (!text.isEmpty()){
        // create a QDataStream operating on the socket
        QDataStream serverStream(m_serverSocket);
        serverStream.setVersion(QDataStream::Qt_5_12);

        // Create the JSON we want to send
        QJsonObject message;
        message["type"] = type;
        message["text"] = text;
        // send the JSON using QDataStream
        serverStream << QJsonDocument(message).toJson();
    }

}
