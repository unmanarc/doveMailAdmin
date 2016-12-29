#ifndef DIALOG_USERS_ADD_H
#define DIALOG_USERS_ADD_H

#include <QDialog>

namespace Ui {
class Dialog_Users_Add;
}

class Dialog_Users_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Users_Add(QWidget *parent = 0);
    ~Dialog_Users_Add();
    void setDomain(const QString & domainName);
    void accept();

    QString getUserName();
    QString getPassword();

private:
    Ui::Dialog_Users_Add *ui;
};

#endif // DIALOG_USERS_ADD_H
