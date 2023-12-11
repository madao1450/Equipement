#include "equipmentoutboundinterface.h"
#include "ui_equipmentoutboundinterface.h"
#include"globle.h"
#include"equipmentoutbound.h"
equipmentoutboundInterface::equipmentoutboundInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::equipmentoutboundInterface)
{
    ui->setupUi(this);

    setWindowTitle("装备出库界面");

    for(int i = 0;i<list_all_equipmentOutbound.size();i++)
    {
        int rom = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rom);
        QStringList list = list_all_equipmentOutbound[i].toStringList();
        for(int i2 = 0;i2<list.size();i2++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(list.at(i2));
            ui->tableWidget->setItem(rom,i2,item);

        }

    }
    connect(ui->return_clicked,SIGNAL(clicked()),this,SLOT(return_clicked()));

}

equipmentoutboundInterface::~equipmentoutboundInterface()
{
    delete ui;
}

void equipmentoutboundInterface::return_clicked()
{
    this->hide();
    EquipmentOutbound *eo  = new EquipmentOutbound;
    eo->show();
}

