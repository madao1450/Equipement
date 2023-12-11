#include "enroll.h"
#include "ui_enroll.h"
#include"mainwindow.h"
#include"question.h"
enroll::enroll(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enroll)
{
    ui->setupUi(this);
    setWindowTitle(QString("注册页面"));
    connect(ui->btn_register,SIGNAL(clicked()),this,SLOT(on_btn_enroll()));
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(on_btn_return()));
}

enroll::~enroll()
{
    delete ui;
}


void enroll::on_btn_enroll()
{
    QString account = ui->account->text();
    QString password = ui->password->text();
    QString password2 =ui->password_2->text();
    QString name = ui->name->text();
    QString age = ui->age->text();
    QString birth = ui->birth->text();
    QString address = ui->address->text();
    QString telphone = ui->telphone->text();
    QString question = ui->question->text();

    QSqlQuery query(db_Connection);
    query.prepare("SELECT account FROM useraccountinfo WHERE account = :account");
    query.bindValue(":account", account);
    if (query.exec() && query.next()) {
        // 账号已存在，不做插入操作
        db_Connection.rollback();
        QMessageBox::warning(this,tr("警告"),tr("账户已存在"));
    } else {
        // 账号不存在，执行插入操作
         if(password2!= password)
        {
            QMessageBox::warning(this,("警告"),tr("密码不一致"));
        }else
        {
        QSqlQuery insert(db_Connection);
        insert.prepare("INSERT INTO useraccountinfo(account, password,name,age,birth,address,telphone,question)"
                       " VALUES(:account, :password,:name,:age,:birth,:address,:telphone,:question)");
        insert.bindValue(":account", account);
        insert.bindValue(":password", password);
        //insert.bindValue(":password2", password2);
        insert.bindValue(":name", name);
        insert.bindValue(":age",age);
        insert.bindValue(":birth",birth);
        insert.bindValue(":address",address);
        insert.bindValue(":telphone",telphone);
        insert.bindValue(":question",question);
        if( insert.exec())
        {
            QMessageBox::information(this,tr("提示"),tr("注册成功"));
        }

        else
        {
            QMessageBox::warning(this,tr("警告"),tr("注册失败"));
            qDebug()<<"Password change failed: "<< insert.lastError();
        }
        this->close();
        }

    }

}

void enroll::on_btn_return()
{

    this->hide();
    MainWindow *w= new MainWindow;
    w->show();

}

