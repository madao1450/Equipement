#ifndef QUESTION_H
#define QUESTION_H

#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class question;
}

class question : public QDialog
{
    Q_OBJECT

public:
    explicit question(QWidget *parent = nullptr);
    ~question();

private slots:
    void on_pushButton_clicked();

private:
    Ui::question *ui;
    QSqlDatabase db_Connection;
};

#endif // QUESTION_H
