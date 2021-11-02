#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include "udprecvsocket.h"

class TcpClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit TcpClientSocket(QObject *parent = nullptr);

    QByteArray read();
    int write(const QByteArray &data);
    bool connect(const QString &ip, int port);
    void disConnect(){socket->disconnectFromHost();}

private:
    QTcpSocket *socket;
};

#endif // TCPCLIENTSOCKET_H
