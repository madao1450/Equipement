#include "accountinfo.h"
#include "ui_accountinfo.h"
#include"administratorinterface.h"
#include"globle.h"
accountInfo::accountInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountInfo)
{
    ui->setupUi(this);
    setWindowTitle(QString("用户信息页面"));

    for(int i = 0;i<list_all_account.size();i++)
    {
        int rom = ui->tableWidget->rowCount();//获取当前表格行数
        ui->tableWidget->insertRow(rom);//表格末尾插入一行
        QStringList romlum  = list_all_account[i].toStringList();
        for(int i = 0;i<romlum.size();i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(romlum.at(i));//显示文本内容
            ui->tableWidget->setItem(rom,i,item);
        }
    }

    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(return_clicked()));


}

accountInfo::~accountInfo()
{
    delete ui;
}


void  accountInfo ::return_clicked()
{
    this->hide();
    list_all_account.clear();
    ui->tableWidget->clear();

    administratorInterface *ai =new administratorInterface;
    ai->show();
}

void accountInfo::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();       // 获得部件当前位置
    this->mousePos = event->globalPos(); // 获得鼠标位置
    this->dPos = mousePos - windowPos ;
}

void accountInfo::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}


