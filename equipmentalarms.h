#ifndef EQUIPMENTALARMS_H
#define EQUIPMENTALARMS_H
#include"globle.h"
#include <QDialog>
#include"mainwindow.h"

namespace Ui {
class equipmentAlarms;
}

class equipmentAlarms : public QDialog
{
    Q_OBJECT

public:
    explicit equipmentAlarms(QWidget *parent = nullptr);
    ~equipmentAlarms();
private slots:
   // void checkedAlarms();
    void on_btn_call_clicked();
    void btn_return_clicked();

private:
    Ui::equipmentAlarms *ui;
    QSqlDatabase db_connection;

    QTimer *timer;

};

#endif // EQUIPMENTALARMS_H
