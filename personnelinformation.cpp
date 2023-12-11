#include "personnelinformation.h"
#include "ui_personnelinformation.h"
#include"globle.h"
#include<QStringList>
#include <QTableWidget>
#include <QHeaderView>
#include <QtXlsx>
#include"administratorinterface.h"
PersonnelInformation::PersonnelInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonnelInformation)
{
    ui->setupUi(this);



    QXlsx::Document xlsx("E:/qt/build-EquipmentManagement-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/equipmentinfo.xlsx");
    //E:/qt/build-EquipmentManagement-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/equipmentoutbound.xlsx
    //E:/qt/build-EquipmentManagement-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/equipmentstorage.xlsx  文件地址
    QXlsx::Worksheet *worksheet = xlsx.currentWorksheet();

    ui-> tableWidget->setColumnCount(worksheet->dimension().columnCount());
    ui->tableWidget->setRowCount(worksheet->dimension().rowCount());
    // 读取Excel数据并添加到表格中
    for (int row = 1; row <= worksheet->dimension().rowCount(); ++row) {
        for (int col = 1; col <= worksheet->dimension().columnCount(); ++col) {
            QXlsx::Cell *cell = worksheet->cellAt(row, col);
            QTableWidgetItem *item = new QTableWidgetItem(cell->value().toString());
            ui-> tableWidget->setItem(row - 1, col - 1, item);
        }
    }


  //ui->tableWidget->resizeColumnsToContents();
    //ui->tableWidget->resizeRowsToContents();


   ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);//自适应
}

PersonnelInformation::~PersonnelInformation()
{
    delete ui;
}

void PersonnelInformation::on_btn_return_clicked()
{
    this->hide();
    administratorInterface *ai = new administratorInterface;
    ai->show();


}

