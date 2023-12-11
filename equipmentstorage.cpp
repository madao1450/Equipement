#include "equipmentstorage.h"
#include "ui_equipmentstorage.h"
#include"administratorinterface.h"
#include"equipmentstorageinterface.h"
#include"globle.h"
#include<QFile>
#include <QXmlStreamWriter>
#include<QSqlRecord>
EquipmentStorage::EquipmentStorage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipmentStorage)
{
    ui->setupUi(this);

  setWindowTitle(QString("装备入库信息填写"));
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(btn_return()));
    connect(ui->btn_look,SIGNAL(clicked()),this,SLOT(look_equipmentStorageInfo()));
    connect(ui->pushButton_increment,SIGNAL(clicked()),this,SLOT(increment()));
    connect(ui->btn_del,SIGNAL(clicked()),this,SLOT(del_equipmentStorageInfo()));
    connect(ui->btn_XML,SIGNAL(clicked()),this,SLOT(XML_clicked()));
    connect(ui->btn_EXCEL,SIGNAL(clicked()),this,SLOT(EXCEL_clicked()));
    connect(ui->btn_modify,SIGNAL(clicked()),this,SLOT(modify()));
}

EquipmentStorage::~EquipmentStorage()
{
    delete ui;
}

void EquipmentStorage::increment()
{
    QString  identifier = ui->lineEdit_id->text();
    QString  time = ui->lineEdit_time->text();
    QString types = ui->lineEdit_types->text();
    QString  number = ui->lineEdit_number->text();
    QString source  = ui->lineEdit_source->text();
    QString personnel = ui->lineEdit_personnel->text();
    QString validity  = ui->lineEdit_valid->text();

    QSqlQuery query(db_connection);
    query.exec("select identifier from equipmentstorage");
    bool T2 = true;
    if(query.next())
    {
        QString id1= query.value(0).toString();

        if(identifier.compare(id1)==0)
        {

            QMessageBox::information(this ,tr("提示") , tr("该编号已存在不允许再次添加!"));
            T2=false;
        }
    }
    if(T2==true){
    query.prepare("insert into equipmentstorage(identifier,types,source,time,number,personnel,vld)values(:identifier,:types,:source,:time,:number,:personnel,:validity)");
    query.bindValue(":identifier", identifier);
    query.bindValue(":types",types);
    query.bindValue(":number",number);
    query.bindValue(":time",time);
    query.bindValue(":source",source);
    query.bindValue(":personnel",personnel);
    query.bindValue(":validity",validity);

    if(query.exec())
    {
            QMessageBox::information(this,tr("good"),tr("添加成功"));
    }
    else
    {
        qDebug()<<query.lastError();
            QMessageBox::warning(this,tr("失败"),tr("添加失败"));
    }
    }
}



void EquipmentStorage::btn_return()
{
    this->hide();

    administratorInterface *ai = new administratorInterface;
    ai->show();
}

void EquipmentStorage::look_equipmentStorageInfo()
{
    QSqlQuery query(db_connection);

    query.exec("select identifier,types,source,time,number,personnel ,vld from equipmentstorage");
  while(query.next())
    {
        QStringList k;
        k.clear();
        QString identifier =query.value(0).toString();
        QString types = query.value(1).toString();
        QString source =query.value(2).toString();
        QString  time=query.value(3).toString();
        QString number =query.value(4).toString();
        QString personnel =query.value(5).toString();
        QString vld =query.value(6).toString();

        k<<identifier<<types<<source<<time<<number<<personnel<<vld;
        list_all_equipmentStorage.append(k);
    }
    for(int i = 0;i<list_all_equipmentStorage.size();i++)
    {
        qDebug()<<list_all_equipmentStorage[i];
    }

    this->hide();
    equipmentstorageInterface *esi = new equipmentstorageInterface;
    esi->show();

}

void EquipmentStorage::del_equipmentStorageInfo()
{
    QString identifier = ui->lineEdit_id->text();
    QSqlQuery query(db_connection);
    query.exec("select identifier,types,source,time,number,personnel,vld from equipmentstorage");
    bool C = true;
    while (query.next())
    {

        QString identifier2 = query.value(0).toString();

        if(identifier.compare(identifier2)==0)
        {
            QString sql;
            sql = QString("delete from equipmentstorage"
                          " where identifier = '%1' ").arg(identifier);
            QSqlQuery query;
            bool ok = query.exec(sql);
            if(ok)
            {

                QMessageBox::information(this ,tr("提示") , tr("删除成功!"));
                C=false;
            }
            else
            {
                QMessageBox::information(this ,tr("提示") , tr("删除失败!"));
                C=false;
            }

        }
    }
    if(C==true)
    {

        QMessageBox::information(this ,tr("提示") , tr("改编号不存在无法删除"));


    }
}

void EquipmentStorage::XML_clicked()
{
    QFile file("E:/qt/EquipmentManagement/equipmentstorage.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "无法创建XML文件";
        return;
    }

    // 创建XML写入器
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true); // 设置自动格式化

    // 写入XML头部
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("data");
    // 执行查询语句
    QSqlQuery query(db_connection);
    query.exec("select *from equipmentstorage");

    // 遍历查询结果，将数据写入XML
    while (query.next())
    {
        xmlWriter.writeStartElement("record");

        // 写入每个字段的值
        xmlWriter.writeTextElement("identifier", query.value(0).toString());
        xmlWriter.writeTextElement("types", query.value(1).toString());
        xmlWriter.writeTextElement("source", query.value(2).toString());
        xmlWriter.writeTextElement("time", query.value(3).toString());
        xmlWriter.writeTextElement("number", query.value(4).toString());
        xmlWriter.writeTextElement("personnel", query.value(5).toString());
        xmlWriter.writeTextElement("vld", query.value(6).toString());


        xmlWriter.writeEndElement(); // 结束当前记录
    }

    xmlWriter.writeEndElement(); // 结束根元素
    xmlWriter.writeEndDocument(); // 结束XML文档

    // 关闭文件
    file.close();
  QMessageBox::information(this,tr("提示"),tr("数据已成功导出为XML文件"));
    qDebug() << "数据已成功导出为XML文件";

}

void EquipmentStorage::EXCEL_clicked()
{
    QSqlQuery query(db_connection);

    if(query.exec("select *from equipmentstorage"))
    {
        QMessageBox::information(this,tr("恭喜"),tr("导出成功"));
    }else
    {
        QMessageBox::warning(this,tr("失败"),"导出失败");

    }


    QXlsx::Document xlsx;
    int row = 1;
    while (query.next()) {
        for (int col = 0; col <  query.record().count(); col++) {
            xlsx.write(row, col + 1, query.value(col).toString());//将查询结果中的值写入Excel文件。该值位于指定的行和列中。",
        }
        row++;
    }
    xlsx.saveAs("equipmentstorage.xlsx");//保存
}

void EquipmentStorage::modify()
{
    QSqlQuery query(db_connection);
    query.prepare("SELECT * FROM equipmentstorage  WHERE identifier = :identifier");
    query.bindValue(":identifier", ui->lineEdit_id->text());

    if (query.exec() && query.next()) {
        QString types = query.value("types").toString();
        QString source = query.value("source").toString();
        QString time  = query.value("time").toString();
        QString number = query.value("number").toString();
        QString personnel = query.value("personnel").toString();
        QString vld  = query.value("vld").toString();


        // 检查用户是否提供了新值，如果提供了则使用新值，否则使用原始记录的值
        if (!ui->lineEdit_types->text().isEmpty()) {
            types= ui->lineEdit_types->text();
        }
        if (!ui->lineEdit_number->text().isEmpty()) {
            number = ui->lineEdit_number->text();
        }
        if (!ui->lineEdit_source->text().isEmpty()) {
            source = ui->lineEdit_source->text();
        }
        if (!ui->lineEdit_time->text().isEmpty()) {
            time = ui->lineEdit_time->text();
        }
        if (!ui->lineEdit_personnel->text().isEmpty()) {
            personnel = ui->lineEdit_personnel->text();
        }
        if (!ui->lineEdit_valid->text().isEmpty()) {
            vld = ui->lineEdit_valid->text();
        }


        query.prepare("UPDATE equipmentstorage SET  types = :types,source= :source, time = :time ,number =:number,personnel = :personnel,"
                      "vld =:vld  WHERE identifier = '"+ui->lineEdit_id->text()+"'");
        query.bindValue(":types",types);
        query.bindValue(":source",source);
        query.bindValue(":time",time);
        query.bindValue(":number",number);
        query.bindValue(":personnel",personnel);
        query.bindValue(":vld",vld);

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
}




