#include "equipmentnews.h"
#include "ui_equipmentnews.h"
#include"equipmentinfo.h"
#include"globle.h"
#include"administratorinterface.h"
#include<QtCore>
#include<QtXml>
#include <QFile>
#include <QXmlStreamWriter>
#include<QSqlRecord>
#include<QTableWidget>
equipmentnews::equipmentnews(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::equipmentnews)
{
    ui->setupUi(this);
setWindowTitle(QString("装备信息"));
    connect(ui->btn_del,SIGNAL(clicked()),this,SLOT(delete_clicked()));
    connect(ui->btn_look,SIGNAL(clicked()),this,SLOT(look()));
    connect(ui->btn_ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(return_clicked()));
    connect(ui->btn_update,SIGNAL(clicked()),this,SLOT(update()));
    connect(ui->btn_XML,SIGNAL(clicked()),this,SLOT(export_XML()));
    connect(ui->btn_EXCEL,SIGNAL(clicked()),this,SLOT(export_EXCEL()));
}

equipmentnews::~equipmentnews()
{
    delete ui;
}

void equipmentnews::update()
{

    QSqlQuery query(db_connection);
    query.prepare("SELECT * FROM equipment WHERE name = :name");
    query.bindValue(":name", ui->lineEdit_name->text());

    if (query.exec() && query.next()) {
        QString classify = query.value("classify").toString();
        QString quality = query.value("quality").toString();
        QString grade = query.value("grade").toString();
        QString ATK = query.value("ATK").toString();
        QString speed = query.value("speed").toString();
        QString additiveAttribute = query.value("additiveAttribute").toString();

        QString otherInfomation = query.value("otherInfomation").toString();

        // 检查用户是否提供了新值，如果提供了则使用新值，否则使用原始记录的值
        if (!ui->lineEdit_classify->text().isEmpty()) {
            classify = ui->lineEdit_classify->text();
        }
        if (!ui->lineEdit_quality->text().isEmpty()) {
            quality = ui->lineEdit_quality->text();
        }
        if (!ui->lineEdit_class->text().isEmpty()) {
            grade = ui->lineEdit_class->text();
        }
        if (!ui->lineEdit_atk->text().isEmpty()) {
            ATK = ui->lineEdit_atk->text();
        }
        if (!ui->lineEdit_speed->text().isEmpty()) {
            speed = ui->lineEdit_speed->text();
        }
        if (!ui->textEdit_additiveAttribute->toPlainText().isEmpty()) {
            additiveAttribute = ui->textEdit_additiveAttribute->toPlainText();
        }
        if (!ui->textEdit_otherInfomation->toPlainText().isEmpty()) {
            otherInfomation = ui->textEdit_otherInfomation->toPlainText();
        }

        // 执行修改操作
        query.prepare("UPDATE equipment SET classify = :classify, quality = :quality, grade= :grade,"
                      "ATK = :ATK, speed = :speed, additiveAttribute = :additiveAttribute,"
                      "otherInfomation = :otherInfomation,  WHERE name = :name");
        query.bindValue(":classify", classify);
        query.bindValue(":quality", quality);
        query.bindValue(":grade", grade);
        query.bindValue(":ATK", ATK);
        query.bindValue(":speed", speed);
        query.bindValue(":additiveAttribute", additiveAttribute);
        query.bindValue(":otherInfomation", otherInfomation);
        query.bindValue(":name", ui->lineEdit_name->text());

        if (query.exec()) {
            QMessageBox::information(this, "Success", "修改成功");
        } else {
            qDebug() << query.lastError();
        }
    } else {
        qDebug() << query.lastError();
    }
}



void equipmentnews::ok_clicked()
{
   // QString id = ui->lineEdit_ID->text();
     QString name = ui->lineEdit_name->text();
     QString classify = ui->lineEdit_classify->text();
     QString quality = ui->lineEdit_quality->text();
     QString grade = ui->lineEdit_class->text();
     QString  ATK = ui->lineEdit_atk->text();
     QString speed = ui->lineEdit_speed->text();
     QString additiveAttribute = ui->textEdit_additiveAttribute->toPlainText();
     QString otherInfomation = ui->textEdit_otherInfomation->toPlainText();

    QSqlQuery query(db_connection);
    query.prepare("insert into equipment(name,classify,quality,grade,ATK,speed,additiveAttribute,otherInfomation)"
              "values(:name,:classify,:quality,:grade,:ATK,:speed,:additiveAttribute,:otherInfomation)");

    //query.bindValue(":id",id);
    query.bindValue(":name",name);
    query.bindValue(":classify",classify);
    query.bindValue(":quality",quality);
    query.bindValue(":grade",grade);
    query.bindValue(":ATK",ATK);
    query.bindValue(":speed",speed);
    query.bindValue(":additiveAttribute",additiveAttribute);
    query.bindValue(":otherInfomation",otherInfomation);

   if (query.exec()) {
    qDebug() << "Data inserted successfully.";
        QMessageBox::information(this,tr("提示"),tr("正确"));
   } else {
    QMessageBox::warning(this,"title","错误");
    qDebug() << "Failed to insert data: " << query.lastError();
   }

  }

 void equipmentnews::look()
  {
    QSqlQuery query(db_connection);
    query.exec("select *from equipment");
    list_all_equipment.clear();
    while (query.next()) {
    QStringList list;
    list.clear();
    QString id =query.value(0).toString();
    QString name = query.value(1).toString();
    QString classify = query.value(2).toString();
    QString quality = query.value(3).toString();
    QString grade = query.value(4).toString();
    QString  ATK = query.value(5).toString();
    QString speed = query.value(6).toString();
    QString additiveAttribute = query.value(7).toString();
    QString otherInfomation = query.value(8).toString();
    list<<id<<name<<classify<<quality<<grade<<ATK<<speed<<additiveAttribute<<otherInfomation;
    list_all_equipment.append(list);
}

    for(int i = 0;i<list_all_equipment.size();i++)
    {
    qDebug()<<list_all_equipment[i];
    }
    this->hide();
    equipmentInfo *info = new equipmentInfo;
    info->show();
}

void equipmentnews::return_clicked()
{
   this->hide();
   list_all_equipment.clear();
   administratorInterface *ad = new administratorInterface;
   ad->show();
}

void equipmentnews::delete_clicked()
{
   QString name = ui->lineEdit_name->text();
   QSqlQuery query(db_connection);
   query.exec("select id,name,classify,quality,grade,ATK,speed,additiveAttribute,otherInfomation  from equipment");
   bool C = true;
   while (query.next())
  {

    QString name2 = query.value(1).toString();

    if(name.compare(name2)==0)
    {
        QString sql;
        sql = QString("delete from equipment"
                      " where name = '%1' ").arg(name);
        QSqlQuery query;
        bool ok = query.exec(sql);
        if(ok)
        {

            QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
           C=false;//找到匹配的结果并成功删除
        }
        else
        {
            QMessageBox::information(this ,tr("提示") , tr("该编号不存在无法删除"));
            C=true;
        }

    }
}

}



void equipmentnews::on_btn_cancle_clicked()
{
close();
}

void equipmentnews::export_XML()
{

      QFile file("E:/qt/EquipmentManagement/equipmentInformation.xml");
      if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
      {
    qDebug() << "无法创建XML文件";
    return;
      }

      QXmlStreamWriter xmlWriter(&file);
      xmlWriter.setAutoFormatting(true); // 设置自动格式化

      // 写入XML头部
      xmlWriter.writeStartDocument();
      xmlWriter.writeStartElement("data");
      // 执行查询语句
      QSqlQuery query(db_connection);
      query.exec("select *from equipment");
      // 遍历查询结果，将数据写入XML
      while (query.next())
      {
    xmlWriter.writeStartElement("record");

    // 写入每个字段的值
    xmlWriter.writeTextElement("id", query.value(0).toString());
    xmlWriter.writeTextElement("name", query.value(1).toString());
    xmlWriter.writeTextElement("classify", query.value(2).toString());
    xmlWriter.writeTextElement("quality", query.value(3).toString());
    xmlWriter.writeTextElement("grade", query.value(4).toString());
    xmlWriter.writeTextElement("ATK", query.value(5).toString());
    xmlWriter.writeTextElement("speed", query.value(6).toString());
    xmlWriter.writeTextElement("additiveAttribute", query.value(7).toString());
    xmlWriter.writeTextElement("otherInfomation", query.value(8).toString());

    xmlWriter.writeEndElement();
      }

      xmlWriter.writeEndElement(); // 结束根元素
      xmlWriter.writeEndDocument(); // 结束XML文档

      // 关闭文件
      file.close();
 QMessageBox::information(this,tr("恭喜"),tr("导出成功"));
      qDebug() << "数据已成功导出为XML文件";


}

void equipmentnews::export_EXCEL()
{
      QSqlQuery query(db_connection);

      if(query.exec("select *from equipment"))
      {
    QMessageBox::information(this,tr("提示"),tr("导出成功"));
      }else
      {
    QMessageBox::warning(this,tr("失败"),"导出失败");

      }


      QXlsx::Document xlsx;
      int row = 1;
      while (query.next()) {
    for (int col = 0; col <  query.record().count(); col++) {//查询结果的字段数量
        xlsx.write(row, col + 1, query.value(col).toString());//将查询结果中的值写入Excel文件。该值位于指定的行和列中。",
    }
    row++;
      }
      xlsx.saveAs("equipmentinfo.xlsx");//保存
}



void equipmentnews::on_btn_XML2_clicked()
{

      QString id = ui->lineEdit_ID->text();
      QString name = ui->lineEdit_name->text();
      QString classify = ui->lineEdit_classify->text();
      QString quality = ui->lineEdit_quality->text();
      QString grade = ui->lineEdit_class->text();
      QString ATK = ui->lineEdit_atk->text();
      QString speed = ui->lineEdit_speed->text();
      QString additiveAttribute = ui->textEdit_additiveAttribute->toPlainText();
      QString otherInfomation = ui->textEdit_otherInfomation->toPlainText();

      QFile file("E:/qt/build-Xmlmport-Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/XML.xml");
      if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Failed to open XML file";
    return;
      }

      QXmlStreamReader xml(&file);

      while (!xml.atEnd() && !xml.hasError()) {
    QXmlStreamReader::TokenType token = xml.readNext();//这行代码读取XML文件的下一个令牌，并将其类型存储在变量token中。

    if (token == QXmlStreamReader::StartElement) {// 这行代码检查令牌的类型是否为StartElement，即开始元素。
        if (xml.name() == "id") {
            id = xml.readElementText();//将文本内容复制给ID
        } else if (xml.name() == "name") {
            name = xml.readElementText();
        } else if (xml.name() == "classify") {
            classify = xml.readElementText();
        } else if (xml.name() == "quality") {
            quality = xml.readElementText();
        } else if (xml.name() == "grade") {
            grade = xml.readElementText();
        } else if (xml.name() == "ATK") {
            ATK = xml.readElementText();
        } else if (xml.name() == "speed") {
            speed = xml.readElementText();
        } else if (xml.name() == "additiveAttribute") {
            additiveAttribute = xml.readElementText();
        } else if (xml.name() == "otherInfomation") {
            otherInfomation = xml.readElementText();
        }
    }
      }

      if (xml.hasError()) {
    qDebug() << "XML parsing error: " << xml.errorString();
      }

      ui->lineEdit_ID->setText(id);
      ui->lineEdit_name->setText(name);
      ui->lineEdit_classify->setText(classify);
      ui->lineEdit_quality->setText(quality);
      ui->lineEdit_class->setText(grade);
      ui->lineEdit_atk->setText(ATK);
      ui->lineEdit_speed->setText(speed);
      ui->textEdit_additiveAttribute->setPlainText(additiveAttribute);
      ui->textEdit_otherInfomation->setPlainText(otherInfomation);

          file.close();

}

