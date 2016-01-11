#ifndef DIALOG_DOMAINS_ADD_H
#define DIALOG_DOMAINS_ADD_H

#include <QDialog>

namespace Ui {
class Dialog_Domains_Add;
}

class Dialog_Domains_Add : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Domains_Add(QWidget *parent = 0);
    ~Dialog_Domains_Add();
    QString getDomain();

private:
    Ui::Dialog_Domains_Add *ui;
};

#endif // DIALOG_DOMAINS_ADD_H
