#ifndef EQUIPMENTOUTBOUNDINTERFACE_H
#define EQUIPMENTOUTBOUNDINTERFACE_H

#include <QDialog>
#include"globle.h"
namespace Ui {
class equipmentoutboundInterface;
}

class equipmentoutboundInterface : public QDialog
{
    Q_OBJECT

public:
    explicit equipmentoutboundInterface(QWidget *parent = nullptr);
    ~equipmentoutboundInterface();
private slots:
    void return_clicked();


private:
    Ui::equipmentoutboundInterface *ui;
};

#endif // EQUIPMENTOUTBOUNDINTERFACE_H
