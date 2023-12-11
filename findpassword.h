#ifndef FINDPASSWORD_H
#define FINDPASSWORD_H

#include <QDialog>

namespace Ui {
class FindPassword;
}

class FindPassword : public QDialog
{
    Q_OBJECT

public:
    explicit FindPassword(QWidget *parent = nullptr);
    ~FindPassword();

private slots:
    void find();
    void return_clicked();
private:
    Ui::FindPassword *ui;
};

#endif // FINDPASSWORD_H
