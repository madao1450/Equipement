#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_btnok_clicked()
{
    QString  name =ui->lineEdit_name->text();
    QString age =ui->lineEdit_age->text();
    QString birth =ui->lineEdit_birth->text();
    QString  telphone =ui->lineEdit_telphone->text();
    QString address =ui->lineEdit_addrss->text();
    QString AffiliatedUnit =ui->lineEdit_affiliat_unit->text();
    QString number = ui->lineEdit_number->text();
    QString description = ui->textEdit_description->toPlainText();

    QSqlQuery query(db_Connection);


    query.prepare("insert into register(name,age,birth,telphone,address,AffiliatedUnit,number,description)values(:name,:age,:birth,:telphone,:address,:AffiliatedUnit,:number,:description)");
    query.bindValue(":name",name);
    query.bindValue(":age",age);
      query.bindValue(":birth",birth);
  query.bindValue(":telphone",telphone);
  query.bindValue(":address",address);
  query.bindValue(":AffiliatedUnit",AffiliatedUnit);
  query.bindValue(":number",number);
  query.bindValue(":description",description);


  if (query.exec()) {
      qDebug() << "Data inserted successfully.";
      QMessageBox::information(this,"title","正确");
  } else {
      QMessageBox::information(this,"title","错误");
      qDebug() << "Failed to insert data: " << query.lastError();
  }

}


void Register::on_btnCancle_clicked()
{
  close();
}

