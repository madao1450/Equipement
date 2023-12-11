#ifndef EQUIPMENTNEWS_H
#define EQUIPMENTNEWS_H
#include"globle.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class equipmentnews;
}

class equipmentnews : public QDialog
{
    Q_OBJECT

public:
    explicit equipmentnews(QWidget *parent = nullptr);
    ~equipmentnews();

private slots:
    void update();
    void ok_clicked();
    void look();
    void return_clicked();
    void delete_clicked();
    void on_btn_cancle_clicked();
    void export_XML();
    void export_EXCEL();
    void on_btn_XML2_clicked();

private:
    Ui::equipmentnews *ui;
    QSqlDatabase db_connection;

};

#endif // EQUIPMENTNEWS_H
