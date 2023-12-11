#include "photo.h"
#include "ui_photo.h"
#include"mainwindow.h"
#include "administratorinterface.h"
#include<QSqlRecord>
#include<QIcon>
#include<QPixmap>
#include<QFileInfo>
#include<QFile>
#include<QFileDialog>
photo::photo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::photo)
{
    ui->setupUi(this);
    setWindowTitle(QString("装备图片查看页面"));
    connect(ui->btn_insert,SIGNAL(clicked()),this,SLOT(insert()));
    connect(ui->btn_browse,SIGNAL(clicked()),this,SLOT(browse()));
    connect(ui->btn_return,SIGNAL(clicked()),this,SLOT(return_clicked()));
}

photo::~photo()
{
    delete ui;
}

void photo::insert()
{

    QString ImagePath =   QFileDialog ::getOpenFileName(this,tr("Select Image"),QCoreApplication::applicationDirPath(),tr("JPG Files (*.jpg)"));//函数打开一个文件对话框，让用户选择一个图片文件。
    QPixmap Image(ImagePath);//读取用户选择的图片文件并将其加载到QPixmap对象中
    QBuffer ImageBuffer;//读写缓冲区
    if(ImageBuffer.open(QIODevice::ReadWrite))
    {
        Image.save(&ImageBuffer,"JPG");//如果成功打开QBuffer，则将图片保存到这个缓冲区，并以JPG格式保存
    }

    QByteArray FinalDataToSave = ImageBuffer.buffer().toBase64();//将缓冲区的数据转换为Base64格式，以文本形式存储或者发送


    QFileInfo FileInfo(ImagePath);//获取图片文件名
    QString ImageNmae = FileInfo.fileName();

    QSqlDatabase::database().transaction();//开启
    QSqlDatabase  db_connection;
    db_connection.open();
    QSqlQuery query(db_connection);
    query.prepare("insert into equipmengphoto(name,dataPhoto)values(:name,:dataPhoto)");
    query.bindValue(":name",ImageNmae);
    query.bindValue(":dataPhoto",FinalDataToSave);

    query.exec();

    db_connection.close();
    QSqlDatabase::database().commit();//提交



    ui->label_insert->setPixmap(Image);
}

void photo::browse()
{
    QByteArray ImageDataFromDatabase;//存储图片数据
    QPixmap Image;
    QString ImageName;
     QSqlDatabase  db_connection;
    db_connection.open();
    QSqlQuery query(db_connection);
    query.prepare("select *from equipmengphoto order by id  desc  limit 1");

    if(query.exec())
    {

        while(query.next())
        {
            ImageName = query.value("name").toString();
            ImageDataFromDatabase = QByteArray::fromBase64(query.value("dataPhoto").toByteArray());

        }

    }
    db_connection.close();

    Image.loadFromData(ImageDataFromDatabase,"JPG");//加载
    //Image.save(QCoreApplication::applicationDirPath()+"/Image_fromDatabase.jpg");保存
    ui->label_browse->setPixmap(Image);
}

void photo::return_clicked()
{
    this->hide();
    administratorInterface *ai= new administratorInterface ;
    ai->show();
}


