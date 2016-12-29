#ifndef DIALOG_DOMAINS_H
#define DIALOG_DOMAINS_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class Dialog_Domains;
}

class Dialog_Domains : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Domains(QWidget *parent = 0);
    ~Dialog_Domains();

protected:
    void showEvent(QShowEvent *event);


private slots:
    void on_pushButton_addDomain_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_remDomain_clicked();

private:
    void addItemToList(QString domainName);
    bool domainExist(QString domainName);
    void refreshDomains();
    Ui::Dialog_Domains *ui;
};

#endif // DIALOG_DOMAINS_H
