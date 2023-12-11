#ifndef ENROLL_H
#define ENROLL_H
#include"globle.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class enroll;
}

class enroll : public QDialog
{
    Q_OBJECT

public:
    explicit enroll(QWidget *parent = nullptr);
    ~enroll();

private slots:

    void on_btn_enroll();

    void on_btn_return();
private:
    Ui::enroll *ui;
    QSqlDatabase db_Connection;

    QTimer *timer;
};

#endif // ENROLL_H
