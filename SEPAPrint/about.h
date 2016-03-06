#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private slots:
    void on_label_linkActivated(const QString &link);

    void on_label_4_linkActivated(const QString &link);

    void on_label_6_linkActivated(const QString &link);

    void on_btnOk_clicked();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
