#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkProxy>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToPLC(const QString &host, quint16 port);
    void sendData(const QByteArray &data);
    void disconnectFromPLC();
    void sendBoolValue(bool value);

signals:
    void dataReceived(const QByteArray &data);
    void connected();
    void disconnected();
    void errorOccurred(const QString &error);
private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *tcpSocket;
};

#endif // TCPCLIENT_H
