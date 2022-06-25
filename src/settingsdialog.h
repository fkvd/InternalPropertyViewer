/***************************************************************************
**           Author: github.com/fkvd                                      **
**             Date: 25.06.2022                                           **
****************************************************************************/

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    void editSpinBoxes(int port);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void editValues(int port);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
