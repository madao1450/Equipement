#include "equipmentoutbound.h"
#include "ui_equipmentoutbound.h"
#include"equipmentoutboundinterface.h"
#include"administratorinterface.h"
#include"globle.h"
#include<QFile>
#include <QXmlStreamWriter>
#include<QSqlRecord>
EquipmentOutbound::EquipmentOutbound(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipmentOutbound)
{
    ui->setupUi(this);
    setWindowTitle(QString("装备出库信息填写"));
    connect(ui->btn_look,SIGNAL(clicked()),this,SLOT(look()));
    connect(ui->btn_ok,SIGNAL(clicked()),this,SLOT(ok()));
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(return_clicked()));
   // connect(ui->btn_del,SIGNAL(clicked()),this,SLOT(del_clicked()));
    connect(ui->btn_XML,SIGNAL(clicked()),this,SLOT(XMl_clicked()));
    connect(ui->btn_EXCEL,SIGNAL(clicked()),this,SLOT(EXCEL_clicked()));
    connect(ui->btn_update,SIGNAL(clicked()),this,SLOT(update()));
}

EquipmentOutbound::~EquipmentOutbound()
{
    delete ui;
}

void EquipmentOutbound::return_clicked()
{
    this->hide();
    administratorInterface *ai =new administratorInterface;
    ai->show();
}



void EquipmentOutbound::look()
{
    QSqlQuery query(db_Connection);

    query.exec("select *from equipmentoutbound");
list_all_equipmentOutbound.clear();//清空列表，避免重复输入
   while(query.next())
    {
        QStringList l;
        l.clear();
        QString identify = query.value(0).toString();
        QString type = query.value(1).toString();
        QString number = query.value(2).toString();
        QString repay = query.value(3).toString();
        QString deliveryDate = query.value(4).toString();
        QString returnDate = query.value(5).toString();
        QString reason = query.value(6).toString();
        QString deliveryPeriod = query.value(7).toString();
        l<<identify<<type<<number<<repay<<deliveryDate<<returnDate<<reason<<deliveryPeriod;
        list_all_equipmentOutbound.append(l);
    }
    for(int i = 0;i<list_all_equipmentOutbound.size();i++)
    {
        qDebug()<<list_all_equipmentOutbound[i];
    }

    this->hide();
    equipmentoutboundInterface *eoi = new equipmentoutboundInterface;
    eoi->show();
}

void EquipmentOutbound::ok()
{
    QString identifier = ui->lineEdit_id->text();
    QString types = ui->lineEdit_types->text();
    QString  outTime = ui->lineEdit_time->text();
    QString returnTime =ui->lineEdit_returntime->text();
    QString reason = ui->lineEdit_reason->text();
    QString number =ui->lineEdit_number->text();
    QString repay = ui->lineEdit_return->text();
    QString deliveryPeriod =ui->lineEdit_returnVaild->text();
    QSqlQuery query(db_Connection);

    query.exec("select identifier from equipmentoutbound");
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
        query.prepare("insert into equipmentoutbound(identifier,types,number,repay,deliveryDate,returnDate,reason,"
                      "deliveryPeriod)values(:identifier,:types,:number,:repay,:outTime,:returnTime,:reason,:deliveryPeriod)");
        query.bindValue(":identifier",identifier);
        query.bindValue(":types",types);
        query.bindValue(":number",number);
        query.bindValue(":repay",repay);
    query.bindValue(":outTime",outTime);
    query.bindValue(":returnTime",returnTime);
    query.bindValue(":reason",reason);
    query.bindValue(":deliveryPeriod",deliveryPeriod);
    if(query.exec())
    {
            QMessageBox::information(this,tr("提示"),"成功");
    }
    else
    {
        qDebug()<<query.lastError();
            QMessageBox::warning(this,tr("警告"),"失败");
    }
    }
}
/*
void EquipmentOutbound::del_clicked()
{
    QString identifier = ui->lineEdit_id->text();
    QSqlQuery query(db_Connection);
    query.exec("select identifier from equipmentoutbound");

    while (query.next())
    {

    QString identifier2 = query.value(0).toString();

    if(identifier.compare(identifier2)==0)
    {
            QString sql;
            sql = QString("delete from equipmentoutbound"
                          " where identifier = '%1' ").arg(identifier);
            QSqlQuery query;
            bool ok = query.exec(sql);
            if(ok)
            {

                QMessageBox::information(this ,tr("提示") , tr("删除成功!"));

            }
            else
            {
                QMessageBox::information(this ,tr("提示") , tr("该编号不存在无法删除"));

            }

    }
    }

}
*/
void EquipmentOutbound::update()
{

    QSqlQuery query(db_Connection);
    query.prepare("SELECT * FROM equipmentoutbound WHERE identifier = :identifier");
    query.bindValue(":identifier", ui->lineEdit_id->text());

    if (query.exec() && query.next()) {
    QString types = query.value("types").toString();
    QString number = query.value("number").toString();
    QString repay = query.value("repay").toString();
    QString deliveryDate = query.value("deliveryDate").toString();
    QString returnDate = query.value("returnDate").toString();
    QString reason = query.value("reason").toString();
    QString deliveryPeriod = query.value("deliveryPeriod").toString();


    // 检查用户是否提供了新值，如果提供了则使用新值，否则使用原始记录的值
    if (!ui->lineEdit_types->text().isEmpty()) {
            types= ui->lineEdit_types->text();
    }
    if (!ui->lineEdit_number->text().isEmpty()) {
            number = ui->lineEdit_number->text();
    }
    if (!ui->lineEdit_time->text().isEmpty()) {
            deliveryDate= ui->lineEdit_time->text();
    }
    if (!ui->lineEdit_return->text().isEmpty()) {
            repay= ui->lineEdit_return->text();
    }
    if (!ui->lineEdit_returntime->text().isEmpty()) {
            returnDate = ui->lineEdit_returntime->text();
    }
    if (!ui->lineEdit_returnVaild->text().isEmpty()) {
            deliveryPeriod = ui->lineEdit_returnVaild->text();
    }

    QSqlQuery query(db_Connection);
    query.prepare("UPDATE equipmentoutbound SET  types = :types,number= :number, repay = :repay ,deliveryDate =:deliveryDate,returnDate = :returnDate,"
                  "reason =:reason ,deliveryPeriod = :deliveryPeriod WHERE identifier = '"+ui->lineEdit_id->text()+"'");
    query.bindValue(":types",types);
    query.bindValue(":number",number);
    query.bindValue(":repay",repay);
    query.bindValue(":deliveryDate",deliveryDate);
    query.bindValue(":returnDate",returnDate);
    query.bindValue(":reason",reason);
    query.bindValue(":deliveryPeriod",deliveryPeriod);
 query.bindValue(":identifier", ui->lineEdit_id->text());
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
void EquipmentOutbound::XMl_clicked()
{
    QFile file("E:/qt/EquipmentManagement/equipmentoutbound.xml");
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
    QSqlQuery query(db_Connection);
    query.exec("select *from equipmentoutbound");

    // 遍历查询结果，将数据写入XML
    while (query.next())
    {
    xmlWriter.writeStartElement("record");

    // 写入每个字段的值
    xmlWriter.writeTextElement("identifier", query.value(0).toString());
    xmlWriter.writeTextElement("types", query.value(1).toString());
    xmlWriter.writeTextElement("number", query.value(2).toString());
    xmlWriter.writeTextElement("repay", query.value(3).toString());
    xmlWriter.writeTextElement("deliveryDate", query.value(4).toString());
    xmlWriter.writeTextElement("returnDate", query.value(5).toString());
    xmlWriter.writeTextElement("reason", query.value(6).toString());

    // ...

    xmlWriter.writeEndElement(); // 结束当前记录
    }

    xmlWriter.writeEndElement(); // 结束根元素
    xmlWriter.writeEndDocument(); // 结束XML文档

    // 关闭文件
    file.close();

    qDebug() << "数据已成功导出为XML文件";
}

void EquipmentOutbound::EXCEL_clicked()
{
    QSqlQuery query(db_Connection);

    if(query.exec("select *from equipmentoutbound"))
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
    xlsx.saveAs("equipmentoutbound.xlsx");//保存
}




