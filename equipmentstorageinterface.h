#ifndef EQUIPMENTSTORAGEINTERFACE_H
#define EQUIPMENTSTORAGEINTERFACE_H

#include <QDialog>

namespace Ui {
class equipmentstorageInterface;
}

class equipmentstorageInterface : public QDialog
{
    Q_OBJECT

public:
    explicit equipmentstorageInterface(QWidget *parent = nullptr);
    ~equipmentstorageInterface();

private slots:
    void btn_Return();
private:
    Ui::equipmentstorageInterface *ui;
};

#endif // EQUIPMENTSTORAGEINTERFACE_H
