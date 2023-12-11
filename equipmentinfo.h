#ifndef EQUIPMENTINFO_H
#define EQUIPMENTINFO_H

#include <QDialog>
#include"globle.h"

namespace Ui {
class equipmentInfo;
}

class equipmentInfo : public QDialog
{
    Q_OBJECT

public:
    explicit equipmentInfo(QWidget *parent = nullptr);
    ~equipmentInfo();

private slots:
    void on_btn_return_clicked();

private:
    Ui::equipmentInfo *ui;
};

#endif // EQUIPMENTINFO_H
