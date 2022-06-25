/***************************************************************************
**           Author: github.com/fkvd                                      **
**             Date: 25.06.2022                                           **
****************************************************************************/

#include "udpreader.h"

UdpReader::UdpReader(int portNumber)
{
    this->portNumber = portNumber;
    socket = new QUdpSocket(this);
    bool result = socket->bind(QHostAddress::LocalHost, this->portNumber);

    if(result)
    {
        connect(socket, SIGNAL(readyRead()), this, SLOT(process()), Qt::DirectConnection);
    }
    else
    {
        qDebug() << "SOCKET_ERROR";
    }
}

UdpReader::~UdpReader()
{
    if(socket){
        socket->close();
        delete socket;
        socket = nullptr;
    }
}

void UdpReader::process()
{
    QHostAddress sender;
    uint16_t port;

    while (socket->hasPendingDatagrams() && !stop)
    {
            QByteArray datagram;
            datagram.resize(socket->pendingDatagramSize());
            socket->readDatagram(datagram.data(), datagram.size(), &sender, &port);
            emit addData(datagram.toDouble());
    }
}

void UdpReader::onStopThread()
{
    stop = true;
    if(socket){
        socket->close();
        delete socket;
        socket = nullptr;
    }

    emit finished();
}
