#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H
#include"globle.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class accountInfo;
}

class accountInfo : public QDialog
{
    Q_OBJECT

public:
    explicit accountInfo(QWidget *parent = nullptr);
    ~accountInfo();

private slots:

    void return_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::accountInfo *ui;
QSqlDatabase db_connection;
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    QTimer *timer;
};

#endif // ACCOUNTINFO_H
