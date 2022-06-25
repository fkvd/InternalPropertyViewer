/***************************************************************************
**           Author: github.com/fkvd                                      **
**             Date: 25.06.2022                                           **
****************************************************************************/

#ifndef UDPREADER_H
#define UDPREADER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QApplication>
#include <QUdpSocket>
#include <QMessageBox>

class UdpReader : public QObject
{
    Q_OBJECT
public:
    UdpReader(int portNumber);
    ~UdpReader();

public slots:
    void process();
    void onStopThread();

signals:
    void finished();
    void addData(double);

private:
    int portNumber;
    bool connected = false;
    volatile bool stop = false;
    QUdpSocket *socket = nullptr;

};

#endif // UDPREADER_H
