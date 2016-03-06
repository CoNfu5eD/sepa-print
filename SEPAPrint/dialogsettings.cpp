#include "dialogsettings.h"
#include "ui_dialogsettings.h"

DialogSettings::DialogSettings(QWidget *parent, QSettings *aAdjust) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    adjust = aAdjust;
    ui->spinX->setValue( adjust->value("x", 0).toInt() );
    ui->spinY->setValue( adjust->value("y", 0).toInt() );
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

void DialogSettings::on_btnApply_clicked()
{

    adjust->setValue( "x", QString::number(ui->spinX->value()) );
    adjust->setValue( "y", QString::number(ui->spinY->value()) );
    accept();
}

void DialogSettings::on_btnCancel_clicked()
{
    reject();
}
