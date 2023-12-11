#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H
#include"globle.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = nullptr);
    ~ChangePassword();

private slots:




    bool checkOldpassword(QString oldPassword ,QString account);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


    void on_btnOld_clicked();

    void on_btn_new_clicked();

private:
    Ui::ChangePassword *ui;
 QSqlDatabase db_Connection;
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    QTimer *timer;
};

#endif // CHANGEPASSWORD_H
