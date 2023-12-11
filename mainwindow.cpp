#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"administratorinterface.h"
#include"register.h"
#include"enroll.h"
#include"userinterface.h"
#include"globle.h"
#include<QTimer>
#include<QDateTime>
#include"findpassword.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("装备管理系统");
    ui->lineEdit_account->setPlaceholderText("输入账号");
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_password->setPlaceholderText("输入密码");

    ui->btn_register->setObjectName("register");
    ui->lineEdit_account->setFocus();
    ui->btn_Log_on->setDefault(true);
    ui->btn_Log_on->setShortcut(Qt::Key_Enter);


    //connect(ui->btn_Log_on,SIGNAL(clicked()),this,SLOT(Input_Judge()));
   // connect(ui->btn_register,SIGNAL(clicked()),this,SLOT(Input_Judge()));
    ui->lineEdit_account->setFrame(false);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit_password->setFrame(false);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(time()));
    this->timer->start();
    this->close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::time()
{
    QTime time = QTime::currentTime();
    QString datetime = time.toString("hh : mm : ss");
    if((time.second()%2)==0)
    {
        datetime[3] = ' ';
        datetime[8] = ' ';
    }
    ui->label_time->setText(datetime);

}

/*
void MainWindow::Input_Judge()
{
    account_this = ui->lineEdit_account->text();
    password_this=ui->lineEdit_password->text();

    if(account_this =="" || password_this=="")QMessageBox::warning(this,"警告","账号密码不能为空");
    else
    {
        QPushButton *button = qobject_cast<QPushButton*>(sender());
        if(button->objectName() == "register")on_btn_register_clicked();
        else on_btn_Log_on_clicked();
    }

}
*/
void MainWindow::on_btn_Log_on_clicked()
{
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();

//管理员
    if(ui->radbtn_admin->isChecked())
    {
        if(account.isEmpty()&&password.isEmpty())
        {
            QMessageBox::warning(this,"title","账号和密码不能为空，请重新输入");
        }
        else if(account== sqluser && password == sqlpass && ui->radbtn_admin)
        {
            QMessageBox::information(this,"提示","正确");
            this->hide();
            administratorInterface ai;
            ai.setModal(true);
            ai.exec();
            this->close();
        }
        else
        {
            QMessageBox::warning(this,"错误","账号或密码错误,请重新输入");
        }
    }
//用户
     if(ui->radbtn_user->isChecked())
    {
        if(account.isEmpty()&&password.isEmpty())
        {
            QMessageBox::warning(this,"title","账号和密码不能为空");
        }
        else
        {
            QSqlQuery query(db_Connection);
            query.exec("select account,password from UserAccountInfo");
            bool C = false;
           while(query.next())
            {
                QString user = query.value(0).toString();
                QString pass = query.value(1).toString();
                //qDebug() << user << pass ;
                if(account.compare(user)==0 && password.compare(pass)==0)
                {
                    C = true;//找到
                    this->hide();
                    userInterface *ui =new userInterface(this);
                    ui->show();

                }

            }
           if(C == false)//没找到
            {
                QMessageBox::warning(this,"title","账号或密码错误,请重新输入");
            }
        }
}


}



void MainWindow::on_btn_register_clicked()
{
    if(ui->radbtn_user->isChecked())
    {
        enroll *en = new enroll(this);
        en->setModal(true);
        en->exec();
    }


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();       // 获得部件当前位置
    this->mousePos = event->globalPos(); // 获得鼠标位置
    this->dPos = mousePos - windowPos ;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
this->move(event->globalPos() - this->dPos);
}


void MainWindow::on_btn_close_clicked()
{
close();
}




void MainWindow::on_btn_findPassword_clicked()
{


if(ui->radbtn_user->isChecked()){
        FindPassword *fp = new FindPassword;
        fp->show();
}


}

