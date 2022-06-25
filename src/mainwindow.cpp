/***************************************************************************
**           Author: github.com/fkvd                                      **
**             Date: 25.06.2022                                           **
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Internal Property Viewer");
    setCentralWidget(ui->widget);

    ui->widget->addGraph();
    ui->widget->xAxis->setLabel("time");
    ui->widget->yAxis->setLabel("value");
    ui->widget->graph(0)->rescaleAxes(true);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    ui->widget->graph(0)->setPen(pen);
    ui->widget->replot();

    auto shortcut = new QShortcut(QKeySequence(tr("Ctrl+S")), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(saveImage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onEditValues(int port)
{
    this->portNumber = port;
}


void MainWindow::on_actionSettings_triggered()
{
    if(settingsDialog)
        delete settingsDialog;

    settingsDialog = new SettingsDialog(this);
    connect(settingsDialog, SIGNAL(editValues(int)), this, SLOT(onEditValues(int)));
    settingsDialog->setWindowTitle("Settings");
    settingsDialog->show();
    settingsDialog->editSpinBoxes(portNumber);
    this->hide();
}


void MainWindow::on_actionStart_triggered()
{

    udpReaderThread = new QThread;
    udpReader = new UdpReader(portNumber);
    udpReader->moveToThread(udpReaderThread);

    connect(udpReaderThread, SIGNAL(started()), udpReader, SLOT(process()));
    connect(udpReader, SIGNAL(finished()), udpReaderThread, SLOT(quit()));
    connect(udpReader, SIGNAL(finished()), udpReader, SLOT(deleteLater()));
    connect(udpReaderThread, SIGNAL(finished()), udpReaderThread, SLOT(deleteLater()));
    connect(this, SIGNAL(stopThread()), udpReader, SLOT(onStopThread()));
    connect(udpReader, SIGNAL(addData(double)), this, SLOT(onAddData(double)));
    udpReaderThread->start();
}


void MainWindow::on_actionStop_triggered()
{
    emit stopThread();
}

void MainWindow::onAddData(double addValue)
{
    value.append(addValue);
    time.append((double)(time.size() + 1));
    ui->widget->graph(0)->setData(time, value);
    ui->widget->graph(0)->rescaleAxes(true);
    ui->widget->replot();
    ui->widget->update();
}

void MainWindow::saveImage()
{
    //emit stopThread();
    QString path = QFileDialog::getSaveFileName(this, "Save Image", QDir::currentPath(), "JPG (*.jpg)");
    ui->widget->saveJpg(path,  0, 0, 1.0, 100);
}

