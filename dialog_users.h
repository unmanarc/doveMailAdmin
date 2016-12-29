#ifndef DIALOG_USERS_H
#define DIALOG_USERS_H

#include <QDialog>
#include <QStringList>
#include <QTreeWidgetItem>

namespace Ui {
class Dialog_Users;
}

class Dialog_Users : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Users(QWidget *parent = 0);
    void setCurrentDomain(const QString &domain);
    ~Dialog_Users();


protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_changePassword_clicked();

    void on_pushButton_addForwarding_clicked();

    void on_pushButton_addNewUser_clicked();

    void on_pushButton_remove_clicked();

private:
    QTreeWidgetItem * createNewUserAtGUI(QString email);
    QTreeWidgetItem *createNewForwardingAtGUI(QString email, QTreeWidgetItem *parent);

    void refreshUserList();

    QStringList getDomainUsers(const QString & domainName);
    QStringList getUserForwardings(const QString & userName);

    Ui::Dialog_Users *ui;
};

#endif // DIALOG_USERS_H
