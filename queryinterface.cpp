#include "queryinterface.h"
#include "ui_queryinterface.h"
#include"equipmentstorageinterface.h"
#include"globle.h"
#include"administratorinterface.h"
#include<QSqlRecord>
#define MAX_PAGE_COUT 2
queryInterface::queryInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::queryInterface)
{
    ui->setupUi(this);
   setWindowTitle(QString("统计查询管理界面"));
    connect(ui->btn_query,SIGNAL(clicked()),this,SLOT(Deliverytime()));
   // connect(ui->btn_query,SIGNAL(clicked()),this,SLOT(equipmentQuery()));
    connect(ui->btn_time_query,SIGNAL(clicked()),this,SLOT(timeQuery()));
    connect(ui->btn_switch,SIGNAL(clicked()),this,SLOT(switchInterface()));
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(return_clicked()));
}

queryInterface::~queryInterface()
{
    delete ui;
}



void queryInterface::Deliverytime()
{
    QString deliveryDate = ui->lineEdit_deliveryDate->text();

    if (deliveryDate.isEmpty()) {
        QMessageBox::warning(this, "提醒", "输入不能为空");
    } else {
        QSqlQuery query(db_Connection);
        query.prepare("select * from equipmentoutbound where deliveryDate = :deliveryDate");
       query.bindValue(":deliveryDate",deliveryDate);

        if (query.exec()) {
            int rowNum = 0;
            int colNum = query.record().count(); // 获取查询结果的列数
            ui->tableWidget_2->setRowCount(query.size());
            ui->tableWidget_2->setColumnCount(colNum); // 设置列数

            while (query.next()) {
                for (int i = 0; i < colNum; i++) {
                    ui->tableWidget_2->setItem(rowNum, i, new QTableWidgetItem(query.value(i).toString()));
                }
                rowNum++;
            }

            if (rowNum == 0) {//没找到结果
                QMessageBox::information(nullptr, "提醒", "没有找到符合条件的查询结果，请重新填写查询时间。");
            }
        }
    }

    db_Connection.close();
}

void queryInterface::return_clicked()
{
    this->hide();
    administratorInterface * ad = new administratorInterface;
    ad->show();

}






void queryInterface::timeQuery()
{

      QString time = ui->lineEdit_queryTime->text();

      if (time.isEmpty()) {
        QMessageBox::information(nullptr, "提醒", "没有找到符合条件的查询结果，请重新填写查询时间。");
      } else {
        QSqlQuery query(db_Connection);
        query.prepare("SELECT  * FROM equipmentstorage WHERE time = :time");
        query.bindValue(":time", time);

        if (query.exec()) {
        int rowNum = 0;
        int colNum = query.record().count(); // 获取查询结果的列数
        ui->tableWidget->setRowCount(query.size());
        ui->tableWidget->setColumnCount(colNum); // 设置列数

        while (query.next()) {
                for (int i = 0; i < colNum; i++) {
                    ui->tableWidget->setItem(rowNum, i, new QTableWidgetItem(query.value(i).toString()));
                }
                rowNum++;
        }

        if (rowNum == 0) {
                QMessageBox::information(nullptr, "提醒", "没有找到符合条件的查询结果，请重新填写查询时间。");
        }
        }
      }

      db_Connection.close();
}
void queryInterface::switchInterface()//在第一个页面和第二页之间面循环
{
      static int i = 0;

      if(++i>=MAX_PAGE_COUT){
        i=0;
      }
      ui->stackedWidget->setCurrentIndex(i % MAX_PAGE_COUT);
}

