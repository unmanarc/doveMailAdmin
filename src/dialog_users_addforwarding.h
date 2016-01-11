#ifndef DIALOG_USERS_ADDFORWARDING_H
#define DIALOG_USERS_ADDFORWARDING_H

#include <QDialog>

namespace Ui {
class Dialog_Users_AddForwarding;
}

class Dialog_Users_AddForwarding : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Users_AddForwarding(QWidget *parent = 0);
    ~Dialog_Users_AddForwarding();

    void setDestination(const QString & to);
    void accept();
    QString getSource();


private:
    Ui::Dialog_Users_AddForwarding *ui;
};

#endif // DIALOG_USERS_ADDFORWARDING_H
