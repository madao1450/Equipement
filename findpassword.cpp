#include "findpassword.h"
#include "ui_findpassword.h"
#include"mainwindow.h"
FindPassword::FindPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPassword)
{
    ui->setupUi(this);
    setWindowTitle(QString("忘记密码页面"));
    connect(ui->btn_find,SIGNAL(clicked()),this,SLOT(find()));
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(return_clicked()));
}

FindPassword::~FindPassword()
{
    delete ui;
}

void FindPassword::find()
{

    QString account = ui->lineEdit_account->text();
    QString newPassword = ui->lineEdit_newPassword->text();
    QString question = ui->lineEdit_question->text();

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.prepare("select account, question from useraccountinfo where account = :account and question = :question");
    query.bindValue(":account", account);
    query.bindValue(":question", question);
    if (query.exec()) {
        if (query.next()) {
            // 账号和问题匹配，更新密码
        query.prepare("update useraccountinfo set password=:password where account = :account and question = :question");
            query.bindValue(":password", newPassword);
            query.bindValue(":account", account);
            query.bindValue(":question", question);
            if (query.exec()) {
                    QMessageBox::information(this,tr("提示"),tr("修改成功"));
        }
        } else {
        QMessageBox::warning(this,tr("警告"),tr("账号或问题信息有误"));
    }
    }

}

void FindPassword::return_clicked()
{
    this->hide();
    MainWindow *mw = new MainWindow;
    mw->show();

}
