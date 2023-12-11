#include "equipmentinfo.h"
#include "ui_equipmentinfo.h"
#include"globle.h"
#include"equipmentnews.h"
equipmentInfo::equipmentInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::equipmentInfo)
{
    ui->setupUi(this);
    setWindowTitle(QString("装备信息页面"));

    for(int i = 0;i<list_all_equipment.size();i++)
    {
        int rol = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rol);
        QStringList roldata = list_all_equipment[i].toStringList();
        for (int i = 0; i < ui->tableWidget->columnCount(); i++) {
            ui->tableWidget->resizeColumnToContents(i);
        }
        for(int i = 0;i<roldata.size();i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(roldata.at(i));
            ui->tableWidget->setItem(rol,i,item);
        }
    }


}

equipmentInfo::~equipmentInfo()
{
    delete ui;
}

void equipmentInfo::on_btn_return_clicked()
{
    this->hide();
    list_all_equipment.clear();
    ui->tableWidget->clear();
    equipmentnews *en = new equipmentnews;
    en->show();
}



