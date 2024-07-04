#include "widget.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <tcpClient.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TcpClient client;
    QObject::connect(&client, &TcpClient::connected, []()
    {
        qDebug() << "Connected to PLC!";
    });

    QObject::connect(&client, &TcpClient::dataReceived, [](const QByteArray &data)
    {
        qDebug() << "Data received from PLC:" << data;
    });

    QObject::connect(&client, &TcpClient::errorOccurred, [](const QString &error) {
        qWarning() << "Error:" << error;
    });

    client.connectToPLC("172.20.80.1", 5555); // 替换为PLC的IP地址和端口号

    QByteArray dataToSend = {"true"}; // 需要发送的数据
    client.sendData(dataToSend);
    client.sendBoolValue(false);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "proxiVisonProject_1_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Widget w;
    w.show();
    return a.exec();
}
