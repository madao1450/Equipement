#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include"globle.h"
#include <QDialog>
#include<QSqlDatabase>
namespace Ui {
class userInterface;
}

class userInterface : public QDialog
{
    Q_OBJECT

public:
    explicit userInterface(QWidget *parent = nullptr);
    ~userInterface();

private slots:



    void modify();
    void look();
    void return_clicked();
    void  delete_clicked();




private:
    Ui::userInterface *ui;
    QSqlDatabase db_Connection;
};

#endif // USERINTERFACE_H
