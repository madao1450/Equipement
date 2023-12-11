#ifndef QUERYINTERFACE_H
#define QUERYINTERFACE_H
#include"globle.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class queryInterface;
}

class queryInterface : public QDialog
{
    Q_OBJECT

public:
    explicit queryInterface(QWidget *parent = nullptr);
    ~queryInterface();

private slots:

    void Deliverytime();
    void return_clicked();

    void timeQuery();
    void switchInterface();

private:
    Ui::queryInterface *ui;
   QSqlDatabase db_Connection;
};

#endif // QUERYINTERFACE_H
