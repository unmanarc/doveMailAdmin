#ifndef DIALOG_CHANGEPASSWORD_H
#define DIALOG_CHANGEPASSWORD_H

#include <QDialog>

namespace Ui {
class Dialog_ChangePassword;
}

class Dialog_ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ChangePassword(QWidget *parent = 0);
    ~Dialog_ChangePassword();
    void accept();
    QString getPassword();

private:
    Ui::Dialog_ChangePassword *ui;
};

#endif // DIALOG_CHANGEPASSWORD_H
