#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    doUpdate();

    if(!QFile(QApplication::applicationDirPath() + "/adjustments.ini").exists())
    {
        QFile nf(QApplication::applicationDirPath() + "/adjustments.ini");
        nf.open(QFile::WriteOnly);
        nf.write(QString("[adjustments]\n").toUtf8());
        nf.write(QString("x=\"0\"\n").toUtf8());
        nf.write(QString("y=\"0\"\n").toUtf8());
        nf.close();
    }
    adjust = new QSettings(QApplication::applicationDirPath() + "/adjustments.ini", QSettings::IniFormat);
    adjust->beginGroup("adjustments");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnPrint_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Landscape);
    printer.setDuplex(QPrinter::DuplexNone);
    printer.setOrientation(QPrinter::Portrait);

    QPrintDialog printdialog(&printer);
    printdialog.setWindowTitle("Überweisung Drucken");
    if(printdialog.exec() == QPrintDialog::Accepted)
    {
        QPainter painter(&printer);
        painter.setFont(QFont("Helvetica Neue,Helvetica,Arial,sans-serif", 12));
        printToPage(&painter, printer.pageRect());

        QRectF pos2 = printer.pageRect();
        pos2.setTop(pos2.top() + 2500);
        printToPage(&painter, pos2);
    }
}

void MainWindow::printToPage(QPainter *p, QRectF sp)
{
    QRectF pos = sp;
    QRectF pos2;
    pos.setLeft(pos.left() + adjust->value("x", 0).toInt() - 40 );
    pos.setTop( pos.top() + adjust->value("y", 0).toInt() + 300 );
    if(ui->beg->text().length() > 27)
    {
        p->drawText(pos, ui->beg->text());
    }else{
        pos2 = pos;
        for(int i = 0; i < ui->beg->text().length(); i++) {
            pos2.setLeft(pos.left() + i * 118);
            p->drawText(pos2, ui->beg->text().at(i));
        }
    }

    pos.setTop( pos.top() + 210 );
    pos2 = pos;
    for(int i = 0; i < ui->begIBAN->text().remove(" ").length(); i++) {
        pos2.setLeft(pos.left() + i * 93);
        p->drawText(pos2, ui->begIBAN->text().remove(" ").at(i));
    }

    pos.setTop( pos.top() + 210 );
    pos2 = pos;
    for(int i = 0; i < ui->begBIC->text().length(); i++) {
        pos2.setLeft(pos.left() + i * 118);
        p->drawText(pos2, ui->begBIC->text().at(i));
    }

    pos.setTop( pos.top() + 185);
    pos2 = pos;
    pos2.setLeft( pos2.left() + 1770 );
    for(int i = 0; i < ui->betrag->text().length(); i++) {
        p->drawText(pos2, ui->betrag->text().at(i));
        pos2.setLeft(pos2.left() + 118);
    }

    pos.setTop( pos.top() + 210);
    pos2 = pos;
    for(int i = 0; i < ui->verwendungszweck->text().length(); i++) {
        pos2.setLeft(pos.left() + i * 118);
        p->drawText(pos2, ui->verwendungszweck->text().at(i));
    }

    pos.setTop( pos.top() + 200);
    pos2 = pos;
    if(ui->nochVerwendungszweck->text().length() > 27)
    {
        p->drawText(pos, ui->nochVerwendungszweck->text());
    }else{
        for(int i = 0; i < ui->nochVerwendungszweck->text().length(); i++) {
            pos2.setLeft(pos.left() + i * 118);
            p->drawText(pos2, ui->nochVerwendungszweck->text().at(i));
        }
    }

    pos.setTop( pos.top() + 200);
    pos2 = pos;
    for(int i = 0; i < ui->inhaber->text().length(); i++) {
        pos2.setLeft(pos.left() + i * 118);
        p->drawText(pos2, ui->inhaber->text().at(i));
    }

    pos.setTop( pos.top() + 200);
    pos2 = pos;
    for(int i = 0; i < ui->inhaberIBAN->text().remove(" ").length(); i++) {
        pos2.setLeft(pos.left() + i * 118);
        if(i > 1) p->drawText(pos2, ui->inhaberIBAN->text().remove(" ").at(i));
    }

    pos.setTop( pos.top() + 350);
    QDate currDate = QDateTime::currentDateTime().date();
    p->drawText(pos, QString( currDate.day() < 10 ? "0" : "" ) + QString::number(currDate.day()) + QString(".") + QString(currDate.month() < 10 ? "0" : "" ) + QString::number(currDate.month()) + QString(".") + QString::number(currDate.year()));
}


void MainWindow::on_btnAbout_clicked()
{
    aboutWindow = new About(this);
    aboutWindow->show();
}

void MainWindow::on_btnOpen_clicked()
{
    QFileDialog fDia(this, windowFlags());
    fDia.setFileMode(QFileDialog::ExistingFile);
    QString fName = fDia.getOpenFileName(
        this,
        tr("Wähle eine Vorlage aus"),
        "",
        tr("Ini Datei (*.ini)")
    );
    if(!fName.isEmpty())
    {
        QSettings settings(fName, QSettings::IniFormat);
        settings.setIniCodec("UTF-8");
        settings.beginGroup("vorlage");
        ui->beg->setText( settings.value("beg").toString() );
        ui->begBIC->setText( settings.value("begBIC").toString() );
        ui->begIBAN->setText( settings.value("begIBAN").toString() );

        ui->inhaber->setText( settings.value("inhaber").toString() );
        ui->inhaberIBAN->setText( settings.value("inhaberIBAN").toString() );

        ui->betrag->setText( settings.value("betrag").toString() );
        ui->verwendungszweck->setText( settings.value("verwendungszweck").toString() );
        ui->nochVerwendungszweck->setText( settings.value("nochVerwendungszweck").toString() );
    }
}

void MainWindow::on_btnSave_clicked()
{
    QFileDialog fDia(this, windowFlags());
    fDia.setFileMode(QFileDialog::AnyFile);
    QString fName = fDia.getSaveFileName(
        this,
        tr("Vorlage Speichern"),
        "",
        tr("Ini Datei (*.ini)")
    );
    if(!fName.isEmpty())
    {
        QFile f(fName);
        f.open(QFile::WriteOnly);
        f.write(QString("[vorlage]\n").toUtf8());
        f.write(QString("beg=\"" + ui->beg->text() + "\"\n").toUtf8());
        f.write(QString("begBIC=\"" + ui->begBIC->text() + "\"\n").toUtf8());
        f.write(QString("begIBAN=\"" + ui->begIBAN->text().remove(" ") + "\"\n").toUtf8());

        f.write(QString("inhaber=\"" + ui->inhaber->text() + "\"\n").toUtf8());
        f.write(QString("inhaberIBAN=\"" + ui->inhaberIBAN->text().remove(" ") + "\"\n").toUtf8());

        f.write(QString("betrag=\"" + ui->betrag->text() + "\"\n").toUtf8());
        f.write(QString("verwendungszweck=\"" + ui->verwendungszweck->text() + "\"\n").toUtf8());
        f.write(QString("nochVerwendungszweck=\"" + ui->nochVerwendungszweck->text() + "\"\n").toUtf8());
        f.close();
    }
}

void MainWindow::on_btnSettings_clicked()
{
    DialogSettings settings(this, adjust);
    settings.exec();
}

void MainWindow::doUpdate()
{
    m_manager = new QNetworkAccessManager(this);

        connect(m_manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(replyDownloadFinished(QNetworkReply*)));

    QNetworkRequest req = QNetworkRequest(QUrl("http://vms.confu5ed.me/sepa-print.latest"));
    m_manager->get(req);
}

void MainWindow::replyDownloadFinished(QNetworkReply* pReply)
{

    QByteArray data = pReply->readAll();
    int newVersion = QString(data).toInt();

    if(newVersion == 0) {
        printf("Aktuelle Version konnte nicht abgerufen werden.");
    }
    if(newVersion > m_version) {
        system(QString(QApplication::applicationDirPath() + "/SEPAPrintUpdater.exe").toStdString().c_str());
    }

}
