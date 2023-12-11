#ifndef EQUIPMENTSTORAGE_H
#define EQUIPMENTSTORAGE_H
#include"globle.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class EquipmentStorage;
}

class EquipmentStorage : public QDialog
{
    Q_OBJECT

public:
    explicit EquipmentStorage(QWidget *parent = nullptr);
    ~EquipmentStorage();

private slots:
    void increment();

    void btn_return();
    void look_equipmentStorageInfo();
    void del_equipmentStorageInfo();
    void XML_clicked();
    void EXCEL_clicked();
    void modify();


private:
    Ui::EquipmentStorage *ui;
    QSqlDatabase db_connection;
};

#endif // EQUIPMENTSTORAGE_H
