#ifndef PERSONNELINFORMATION_H
#define PERSONNELINFORMATION_H

#include <QDialog>
#include"globle.h"
namespace Ui {
class PersonnelInformation;
}

class PersonnelInformation : public QDialog
{
    Q_OBJECT

public:
    explicit PersonnelInformation(QWidget *parent = nullptr);
    ~PersonnelInformation();

private slots:
    void on_btn_return_clicked();

private:
    Ui::PersonnelInformation *ui;
};

#endif // PERSONNELINFORMATION_H
