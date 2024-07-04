#include "tcpclient.h"

TcpClient::TcpClient( QObject *parent)
    : QObject(parent), tcpSocket(new QTcpSocket(this))
{
    // 禁用代理
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::NoProxy);
    QNetworkProxy::setApplicationProxy(proxy);

    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(tcpSocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(tcpSocket, qOverload<QAbstractSocket::SocketError>(&QTcpSocket::errorOccurred), this, &TcpClient::onErrorOccurred);
}

void TcpClient::connectToPLC(const QString &host, quint16 port)
{
    tcpSocket->connectToHost(host, port);
}

void TcpClient::sendData(const QByteArray &data)
{
    if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        tcpSocket->write(data);
    }
}

void TcpClient::sendBoolValue(bool value)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian); // 根据需要设置字节序
    stream << value;
    tcpSocket->write(data);
}

void TcpClient::disconnectFromPLC()
{
    tcpSocket->disconnectFromHost();
}

void TcpClient::onReadyRead()
{
    QByteArray data = tcpSocket->readAll();
    emit dataReceived(data);
}

void TcpClient::onConnected()
{
    emit connected();
}

void TcpClient::onDisconnected()
{
    emit disconnected();
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    emit errorOccurred(tcpSocket->errorString());
}
