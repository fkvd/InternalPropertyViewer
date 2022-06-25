/***************************************************************************
**           Author: github.com/fkvd                                      **
**             Date: 25.06.2022                                           **
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsdialog.h"
#include "udpreader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void stopThread();

private slots:
    void on_actionSettings_triggered();
    void onEditValues(int port);
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void onAddData(double addValue);
    void saveImage();

private:
    Ui::MainWindow *ui;
    SettingsDialog *settingsDialog = nullptr;
    UdpReader *udpReader = nullptr;
    QThread* udpReaderThread = nullptr;
    int portNumber = 2323;
    QVector<double> time;
    QVector<double> value;
};
#endif // MAINWINDOW_H
