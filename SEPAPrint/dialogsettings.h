#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QWidget *parent = 0, QSettings *aAdjust = 0);
    ~DialogSettings();

private slots:
    void on_btnApply_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DialogSettings *ui;
    QSettings *adjust;
};

#endif // DIALOGSETTINGS_H
