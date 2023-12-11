#ifndef PHOTO_H
#define PHOTO_H

#include <QDialog>
#include"globle.h"
namespace Ui {
class photo;
}

class photo : public QDialog
{
    Q_OBJECT

public:
    explicit photo(QWidget *parent = nullptr);
    ~photo();

private slots:
    void insert();
    void browse();
    void return_clicked();

private:
    Ui::photo *ui;
};

#endif // PHOTO_H
