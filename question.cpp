#include "question.h"
#include "ui_question.h"
#include"mainwindow.h"
question::question(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::question)
{
    ui->setupUi(this);
}

question::~question()
{
    delete ui;
}

void question::on_pushButton_clicked()
{
    QString answer = ui->lineEdit_answer->text();
    QString account = ui->lineEdit_account->text();
    QSqlQuery query(db_Connection);


    query.prepare("insert into question(account,answer) values(:account,:answer)");
    query.bindValue(":account",account);
    query.bindValue(":answer", answer);

    if (query.exec()) {
        qDebug() << "Data inserted successfully.";
        QMessageBox::information(this,"title","正确");
    } else {
        QMessageBox::information(this,"title","错误");
        qDebug() << "Failed to insert data: " << query.lastError();

    }









}

