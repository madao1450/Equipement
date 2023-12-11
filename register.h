#ifndef REGISTER_H
#define REGISTER_H
#include"globle.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_btnok_clicked();

    void on_btnCancle_clicked();

private:
    Ui::Register *ui;
    QSqlDatabase db_Connection;
};

#endif // REGISTER_H
