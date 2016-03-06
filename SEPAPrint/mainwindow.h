#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFileDialog>
#include <QtNumeric>
#include <QPainter>
#include <QDateTime>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "about.h"
#include "dialogsettings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnPrint_clicked();

    void on_btnAbout_clicked();

    void on_btnOpen_clicked();

    void on_btnSave_clicked();

    void on_btnSettings_clicked();

    void replyDownloadFinished(QNetworkReply* pReply);

private:
    Ui::MainWindow *ui;
    About *aboutWindow = NULL;
    QSettings *adjust;
    int m_version = 102;
    QNetworkAccessManager *m_manager;
    void printToPage(QPainter *p, QRectF sp);
    void doUpdate();
};

#endif // MAINWINDOW_H
