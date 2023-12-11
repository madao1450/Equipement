#ifndef ADMINISTRATORINTERFACE_H
#define ADMINISTRATORINTERFACE_H

#include <QDialog>
#include<QSqlDatabase>
#include"accountinfo.h"
#include"globle.h"
namespace Ui {
class administratorInterface;
}

class administratorInterface : public QDialog
{
    Q_OBJECT
private:
    Ui::administratorInterface *ui;
    QDialog *dialog;
    QSqlDatabase db_Connection;
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
public:
    explicit administratorInterface(QWidget *parent = nullptr);
    ~administratorInterface();





private slots:
    void call();
    void return_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void picturebrowsing();
    void accountInfos();
    void equipmentInfo();
    void equipmentStorage();
    void equipmentOutbound();
    void statisticsQuery();
    void on_btn_import_clicked();
};

#endif // ADMINISTRATORINTERFACE_H
