#include "userinterface.h"
#include "ui_userinterface.h"
#include"register.h"
#include"mainwindow.h"
#include"globle.h"
userInterface::userInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userInterface)
{
    ui->setupUi(this);
setWindowTitle(QString("客户端"));

    connect(ui->btn_modify,SIGNAL(clicked()),this,SLOT(modify()));
    connect(ui->btn_look,SIGNAL(clicked()),this,SLOT(look()));
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(return_clicked()));
    connect(ui->btn_del,SIGNAL(clicked()),this,SLOT(delete_clicked()));
}

userInterface::~userInterface()
{
    delete ui;
}

void userInterface::modify()
{
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();
    QString name = ui->lineEdit_name->text();
    QString age = ui->lineEdit_age->text();
    QString birth = ui->lineEdit_birth->text();
    QString address = ui->lineEdit_address->text();
    QString telphpne = ui->lineEdit_telphone->text();
    QString question = ui->lineEdit_question->text();
    QSqlQuery query(db_Connection);
    query.prepare("UPDATE UserAccountInfo SET  password = :password,name = :name, age = :age ,birth =:birth,address = :address,telphone =:telphone,question = :question WHERE account = '"+account+"'");
    query.bindValue(":name",name);
    query.bindValue(":age",age);
    query.bindValue(":birth",birth);
    query.bindValue(":address",address);
    query.bindValue(":telphone",telphpne);
    query.bindValue(":password",password);
    query.bindValue(":question",question);


    if(query.exec())
    {
        QMessageBox::information(this,tr("提示"),tr("修改成功"));
    }
    else
    {
        qDebug()<<query.lastError();
        QMessageBox::warning(this,tr("警告"),tr("修改失败"));
    }
}



void userInterface::look()
{
    QString account = ui->lineEdit_account->text();
    QSqlQuery query(db_Connection);
    query.exec("select account,password,name,age,birth,address,telphone,question from useraccountinfo where account = '"+account+"'");

    if(query.next())
    {
        qDebug()<<"第一条数据"<<query.value(0).toString();
        ui->lineEdit_account->setText(query.value(0).toString());
        ui->lineEdit_password->setText(query.value(1).toString());
        ui->lineEdit_name->setText(query.value(2).toString());
        ui->lineEdit_age->setText(query.value(3).toString());
        ui->lineEdit_birth->setText(query.value(4).toString());
        ui->lineEdit_address->setText(query.value(5).toString());
        ui->lineEdit_telphone->setText(query.value(6).toString());
        ui->lineEdit_question->setText(query.value(7).toString());
    }
    else
    {
        if(account.compare("")==0 )
        {
            QMessageBox::warning(this,tr("警告"),tr("不能为空"));
        }
    }
}

void userInterface::return_clicked()
{
    this->hide();
    MainWindow *ui = new MainWindow;
    ui->show();
}

void userInterface::delete_clicked()
{
    QString account = ui->lineEdit_account->text();
    QSqlQuery query(db_Connection);
    query.prepare("delete from UserAccountInfo  where account = :account");
    query.bindValue(":account",account);

    if(query.exec())
    {
        QMessageBox::information(this,tr("提示"),tr("删除成功"));
    }
    else
    {
        qDebug()<<query.lastError();
        QMessageBox::warning(this,tr("警告"),tr("删除失败"));
    }
}







