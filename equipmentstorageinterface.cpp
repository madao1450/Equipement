#include "equipmentstorageinterface.h"
#include "ui_equipmentstorageinterface.h"
#include"globle.h"
#include"equipmentstorage.h"
equipmentstorageInterface::equipmentstorageInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::equipmentstorageInterface)
{
    ui->setupUi(this);


    setWindowTitle(QString("装备入库信息页面"));

    for(int i = 0;i<list_all_equipmentStorage.size();i++)
    {
        int rom = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rom);
        QStringList romlum  = list_all_equipmentStorage[i].toStringList();
        for(int i = 0;i<romlum.size();i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(romlum.at(i));
            ui->tableWidget->setItem(rom,i,item);
        }
    }
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(btn_Return()));
}

equipmentstorageInterface::~equipmentstorageInterface()
{
    delete ui;
}

void equipmentstorageInterface::btn_Return()
{
    this->hide();
    list_all_equipmentStorage.clear();
    ui->tableWidget->clear();
    EquipmentStorage *eqs = new EquipmentStorage;
    eqs->show();
}

