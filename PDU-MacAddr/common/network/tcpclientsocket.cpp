#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);

}

bool TcpClientSocket::connect(const QString &ip, int port)
{
    socket->abort();  //取消已有的连接
    socket->connectToHost(ip, port); //连接服务器
    return  socket->waitForConnected(1000);
}


int TcpClientSocket::write(const QByteArray &data)
{
    int ret = 0;
    if(socket->isWritable()) {
        ret = socket->write(data);
        socket->flush();
    }

    return ret;
}

QByteArray TcpClientSocket::read()
{
    QByteArray array;
    if(socket->isReadable()) {
    array = socket->readAll();
    }

    return array;
}
