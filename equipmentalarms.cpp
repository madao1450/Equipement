#include "equipmentalarms.h"
#include "ui_equipmentalarms.h"
#include<QDate>
#include<QSqlQueryModel>
#include<QMessageBox>
#include "administratorinterface.h"
#include"globle.h"
equipmentAlarms::equipmentAlarms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::equipmentAlarms)
{
    ui->setupUi(this);

    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(btn_return_clicked()));
   setWindowTitle(QString("装备报警页面"));
    connect(ui->btn_call,SIGNAL(clicked()),this,SLOT(on_btn_call_clicked()));

}

equipmentAlarms::~equipmentAlarms()
{
    delete ui;
}

void equipmentAlarms::on_btn_call_clicked()
{

    QString deliveryPeriod = ui->lineEdit_indetify->text();
    QString queryStr = "select identifier, types, number, repay, deliveryDate, returnDate, reason, deliveryPeriod from equipmentoutbound where deliveryPeriod >= ?";
    QSqlQuery query(db_connection);
    query.prepare(queryStr);
    query.addBindValue(deliveryPeriod.toInt());

    if (query.exec()) {
        int rowNum = 0;
        int column = query.record().count();//获取查询结果的列数
        ui->tableWidget->setRowCount(query.size());//表格行数
        ui->tableWidget->setColumnCount(column);
        QMessageBox::warning(this,tr("警告"),tr("这些装备已经超期"));
        while(query.next()) {

            for(int i = 0;i<column;i++)//循环列数
            {
                ui->tableWidget->setItem(rowNum,i,new QTableWidgetItem(query.value(i).toString()));
            }
            rowNum++;//增加行数
        }
    }

}

void equipmentAlarms::btn_return_clicked()
{
this->hide();
administratorInterface *ai = new administratorInterface;
ai->show();
}
