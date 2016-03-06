#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    doDownload();
}

void MainWindow::doDownload()
{
    m_manager = new QNetworkAccessManager(this);
    QNetworkRequest req = QNetworkRequest(QUrl("http://vms.confu5ed.me/files/sepa-print.cab"));
    m_reply = m_manager->get(req);


    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
         this, SLOT(replyDownloadFinished(QNetworkReply*)));
    connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)),
         this, SLOT(updateDownloadProgress(qint64,qint64)));
    connect(m_reply, SIGNAL(readyRead()),
         this, SLOT(httpReadyRead()));


    m_file = new QFile(QApplication::applicationDirPath() + "/sepa-print.cab");
    ui->plainTextEdit->appendPlainText(QString("Download der Datei sepa-print.cab"));
    if(m_file->exists())
        m_file->remove();
    m_file->open(QFile::Append);

}

void MainWindow::updateDownloadProgress(qint64 bytesRead, qint64 bytesTotal)
{
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesRead);
}

void MainWindow::replyDownloadFinished(QNetworkReply* pReply)
{
    m_file->flush();
    m_file->close();
    ui->plainTextEdit->appendPlainText(QString("Download Abgeschlossen."));
    ui->plainTextEdit->repaint();
    ui->plainTextEdit->appendPlainText(QString("Entpacken der Datei sepa-print.cab"));
    ui->plainTextEdit->repaint();
    QProcess p;
    p.start(QString("expand \"%1\" -F:* \"%2\"").arg(QApplication::applicationDirPath() + "/sepa-print.cab").arg(QApplication::applicationDirPath() + "/").toStdString().c_str());
    p.waitForFinished();
    ui->plainTextEdit->appendPlainText(QString("Update Abgeschlossen."));
}

void MainWindow::httpReadyRead()
{
    if(m_file)
        m_file->write(m_reply->readAll());
}
