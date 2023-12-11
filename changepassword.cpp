#include "changepassword.h"
#include "ui_changepassword.h"
#include"mainwindow.h"

ChangePassword::ChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);



}

ChangePassword::~ChangePassword()
{
    delete ui;
}


bool ChangePassword::checkOldpassword(QString oldPassword, QString account)
{

    QSqlQuery query(db_Connection);

    query.prepare("SELECT password FROM UserAccountInfo WHERE account = :account");
    query.bindValue(":account",account);

    if(query.exec()&&query.next())
    {
        if(query.size()>0){
            QString passWord = query.value(0).toString();
            if(passWord==oldPassword)
            {
                return true;
            }
        }
    }
    else{
        qDebug()<<"Failed to execute query:"<<query.lastError().text();
    }
    return false;
}

void ChangePassword::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();       // 获得部件当前位置
    this->mousePos = event->globalPos(); // 获得鼠标位置
    this->dPos = mousePos - windowPos ;
}

void ChangePassword::mouseMoveEvent(QMouseEvent *event)
{
 this->move(event->globalPos() - this->dPos);
}

void ChangePassword::on_btnOld_clicked()
{
   QString account =ui->lineEdit_account->text();
   QString oldPassword = ui->lineEdit_old->text();

   bool result = checkOldpassword(oldPassword,account);
   if(result)
   {
        QMessageBox::information(this,"提示","原密码正确");
        qDebug()<<"The original password is correct";
   }
   else
   {
        QMessageBox::warning(this,"提示","密码错误");
        qDebug()<<"Original password error";
   }



}


void ChangePassword::on_btn_new_clicked()
{
   QString account = ui->lineEdit_account2->text();
   QString newPassword = ui->lineEdit_new->text();
    QSqlQuery queryNew(db_Connection);
    queryNew.prepare("UPDATE UserAccountInfo SET password = :newpassword WHERE account = :account");
    queryNew.bindValue(":newpassword",newPassword);
   queryNew.bindValue(":account",account);

    if(queryNew.exec()){
        QMessageBox::information(this,"title","修改成功");
        qDebug()<<"Password changed successfully";
   }
    else
    {
        QMessageBox::warning(this,"title","修改失败");
        qDebug()<<"Password change failed: "<<queryNew.lastError();
    }
}

