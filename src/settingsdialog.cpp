/***************************************************************************
**           Author: github.com/fkvd                                      **
**             Date: 25.06.2022                                           **
****************************************************************************/

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::editSpinBoxes(int port)
{
    ui->spinBoxPortNumber->setValue(port);
}

void SettingsDialog::on_buttonBox_accepted()
{
    int port   = ui->spinBoxPortNumber->value();
    emit editValues(port);
    parentWidget()->setVisible(true);
}


void SettingsDialog::on_buttonBox_rejected()
{
    parentWidget()->setVisible(true);
}

