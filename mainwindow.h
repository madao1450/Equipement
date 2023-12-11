#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QSqlDatabase>
#include<QSqlDriver>
#include<QSqlError>
#include<QDebug>
#include<QSqlQuery>
#include <QMainWindow>
#include<QString>
#include<QSql>
#include<QStackedWidget>
#include<QMessageBox>
#include <QDialog>
#include <QtCore>
#include "xlsxdocument.h"
#include<QtGui>
#include<QSqlRecord>
#include<QIcon>
#include<QPixmap>
#include<QFileInfo>
QT_BEGIN_NAMESPACE
#include<QTimer>
#include"globle.h"
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void time();
    //void Input_Judge();
    void on_btn_Log_on_clicked();

    void on_btn_register_clicked();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void on_btn_close_clicked();

    void on_btn_findPassword_clicked();

private:
    Ui::MainWindow *ui;
    QMessageBox *messagebox;

 QSqlDatabase db_Connection;
    QString account_this;
 QString password_this;

    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    QTimer *timer;
};
#endif // MAINWINDOW_H
