#ifndef EQUIPMENTOUTBOUND_H
#define EQUIPMENTOUTBOUND_H
#include"globle.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class EquipmentOutbound;
}

class EquipmentOutbound : public QDialog
{
    Q_OBJECT

public:
    explicit EquipmentOutbound(QWidget *parent = nullptr);
    ~EquipmentOutbound();

private slots:
    void return_clicked();
    void look();
    void ok();
    //void del_clicked();
    void update();
    void XMl_clicked();
    void EXCEL_clicked();

private:
    Ui::EquipmentOutbound *ui;
        QSqlDatabase db_Connection;
};

#endif // EQUIPMENTOUTBOUND_H
