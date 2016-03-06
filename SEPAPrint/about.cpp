#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}

void About::on_label_linkActivated(const QString &link)
{
    system("explorer http://confu5ed.me");
}

void About::on_label_4_linkActivated(const QString &link)
{
    system("explorer http://serious-pro.de");
}

void About::on_label_6_linkActivated(const QString &link)
{
    system(QString("explorer %1").arg(link).toStdString().c_str());
}

void About::on_btnOk_clicked()
{
    close();
}
