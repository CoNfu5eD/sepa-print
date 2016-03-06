#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QByteArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void doDownload();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void updateDownloadProgress(qint64 bytesRead, qint64 bytesTotal);
    void replyDownloadFinished(QNetworkReply* pReply);
    void httpReadyRead();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *m_manager;
    QFile *m_file;
    QNetworkReply *m_reply;
};

#endif // MAINWINDOW_H
