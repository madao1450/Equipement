#include "administratorinterface.h"
#include "ui_administratorinterface.h"
#include"mainwindow.h"
#include<QTableWidgetItem>
#include"accountinfo.h"
#include"globle.h"
#include"personnelinformation.h"
#include"equipmentinfo.h"
#include"equipmentnews.h"
#include"equipmentstorage.h"
#include"equipmentoutbound.h"
#include"queryinterface.h"
#include"equipmentalarms.h"
#include"photo.h"
administratorInterface::administratorInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::administratorInterface)
{
    ui->setupUi(this);
      setWindowTitle(QString("管理端"));
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(return_clicked()));
    connect(ui->btn_UserManagement,SIGNAL(clicked()),this,SLOT(accountInfos()));
    connect(ui->btn_equipmentInfo,SIGNAL(clicked()),this,SLOT(equipmentInfo()));
    connect(ui->btn_EquipmentStorage,SIGNAL(clicked()),this,SLOT(equipmentStorage()));
    connect(ui->btn_EquipmentOutbound,SIGNAL(clicked()),this,SLOT(equipmentOutbound()));
    connect(ui->btn_query,SIGNAL(clicked()),this,SLOT(statisticsQuery()));
    connect(ui->btn_callmange,SIGNAL(clicked()),this,SLOT(call()));
    connect(ui->btn_picturebrowsing,SIGNAL(clicked()),this,SLOT(picturebrowsing()));
    this->setWindowFlags(Qt::FramelessWindowHint);
}

administratorInterface::~administratorInterface()
{
    delete ui;
}

//转到报警页面
void administratorInterface::call()
{
    this->hide();
    equipmentAlarms *ea = new equipmentAlarms;
    ea->show();

}
//返回
void administratorInterface::return_clicked()
{
    this->hide();
    MainWindow *ui = new MainWindow;
    ui->show();
}

void administratorInterface::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();       // 获得部件当前位置
    this->mousePos = event->globalPos(); // 获得鼠标位置
    this->dPos = mousePos - windowPos ;
}

void administratorInterface::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

//装备图片
void administratorInterface::picturebrowsing()
{
    this->hide();
    photo *ph = new photo;
    ph->show();
}

//账户信息
void administratorInterface::accountInfos()
{
    QSqlQuery query(db_Connection);

    query.exec("select *from UserAccountInfo;");
    qDebug()<<query.lastError();
    while(query.next())
    {
        QStringList k;//存储从数据库查询获得的数据
        k.clear();
        QString id =query.value(0).toString();
        QString account = query.value(1).toString();
        QString password =query.value(2).toString();
        QString  name =query.value(3).toString();
        QString age =query.value(4).toString();
        QString birth =query.value(5).toString();
        QString address =query.value(6).toString();
        QString telphone =query.value(7).toString();
        QString question = query.value(8).toString();
        k<<id<<account<<password<<name<<age<<birth<<address<<telphone<<question;//添加到k中
        list_all_account.append(k);//将k对象添加到列表中
    }
    for(int i = 0;i<list_all_account.size();i++)//遍历
    {
        qDebug()<<list_all_account[i];//输出账户信息
    }
    this->hide();
    accountInfo *ac =new accountInfo;
    ac->show();
}


//装备信息
void administratorInterface::equipmentInfo()
{
    equipmentnews *equip = new equipmentnews(this);
    equip->show();
}
//装备入库
void administratorInterface::equipmentStorage()
{
    EquipmentStorage *es = new EquipmentStorage(this);
    es->show();

}
//装备出库
void administratorInterface::equipmentOutbound()
{
    EquipmentOutbound * eq = new EquipmentOutbound(this);
    eq->show();
}
//统计查询
void administratorInterface::statisticsQuery()
{
    queryInterface *qi = new queryInterface(this);
    qi->show();
}



void administratorInterface::on_btn_import_clicked()
{

    PersonnelInformation *pi = new PersonnelInformation;
    pi->show();
}

