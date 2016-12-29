/**
 *  @author  Aaron Mizrachi (aaron@unmanarc.com)
 *  @date    29/12/2016
 *  @version 1.0
 *
 *  @brief Dovecot Mail Administration
 *
 *  @section DESCRIPTION
 *
 *  This is a little program to organize your emails on
 *  your private email server (dovecot+postfix+mysql based)
 *
 *  If you need support or any new features please feel free
 *  to contact me.
 *
 *  Telegram: @unmanarc
 *  Email:    aaron@unmanarc.com
 *  Github:   /unmanarc
 *  Web:      https://www.unmanarc.com/
 *
 */
#include "dialog_domains.h"
#include "ui_dialog_domains.h"

#include "dialog_users.h"
#include "dialog_domains_add.h"
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlDriver>
#include <QSqlError>
#include <QMessageBox>

#include <QDebug>

Dialog_Domains::Dialog_Domains(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Domains)
{
    ui->setupUi(this);
}

Dialog_Domains::~Dialog_Domains()
{
    delete ui;
}

void Dialog_Domains::showEvent(QShowEvent *event)
{
    refreshDomains();
}

void Dialog_Domains::refreshDomains()
{
    QSqlDatabase db = QSqlDatabase::database("db");
    QSqlQuery query(db);
    query.exec("SELECT domain FROM domains;");
    ui->listWidget->clear();
    while (query.next())
    {
        addItemToList(query.value(0).toString());
    }
}

void Dialog_Domains::on_pushButton_addDomain_clicked()
{
    Dialog_Domains_Add domainadd;
    while (domainadd.exec())
    {
        if (domainadd.getDomain().isEmpty())
        {
            QMessageBox::warning(this,"Add Domain", "Please choose a domain name (not empty)");
        }
        else if (domainExist(domainadd.getDomain()))
        {
            QMessageBox::warning(this,"Add Domain", "Please choose another domain name (domain already exist)");
        }
        else
        {
            // Create the domain here.
            QSqlDatabase db = QSqlDatabase::database("db");
            QSqlQuery query(db);
            query.prepare("INSERT INTO domains(`domain`) VALUES(?);");
            query.addBindValue(domainadd.getDomain());
            if (!query.exec())
            {
                QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
            }
            else
            {
                addItemToList(domainadd.getDomain());
                break;
            }
        }
    }
}

void Dialog_Domains::addItemToList(QString domainName)
{
    QListWidgetItem * item = new QListWidgetItem(ui->listWidget);
    item->setText(domainName);
    item->setIcon(QIcon("://icons/mail.svg"));
}

bool Dialog_Domains::domainExist(QString domainName)
{
    QSqlDatabase db = QSqlDatabase::database("db");
    QSqlQuery query(db);
    query.prepare("SELECT domain FROM domains WHERE domain=?;");
    query.addBindValue(domainName);
    if (!query.exec())
    {
        QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
        return true;
    }
    if (query.next()) return true;
    return false;
}

void Dialog_Domains::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;
    setDisabled(true);
    Dialog_Users users(this);
    users.setCurrentDomain(item->text());
    users.exec();
    setDisabled(false);
}

void Dialog_Domains::on_pushButton_remDomain_clicked()
{
    QListWidgetItem * item = ui->listWidget->currentItem();
    if (!item)
    {
        QMessageBox::warning(this,"Remove Item","Please select an item before.");
        return;
    }

    QString domainName=item->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, windowTitle(), "Remove " + domainName + "?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No)
    {
        QMessageBox::information(this, windowTitle(), "Aborted");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("db");
    QSqlQuery query(db);

    if (1)
    {
        query.prepare("DELETE FROM domains WHERE domain=?;");
        query.addBindValue(domainName);
        if (!query.exec())
        {
            QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
            return;
        }
    }

    if (1)
    {
        QSqlField f;
        f.setType(QVariant::String);
        f.setValue(domainName);

        QString queryV = "DELETE FROM users WHERE email LIKE '%@" + db.driver()->formatValue(f).mid(1) +  ";";
        qDebug() << "Query: " << queryV;

        if (!query.exec(queryV))
        {
            QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
            return;
        }
    }

    if (1)
    {
        QSqlField f;
        f.setType(QVariant::String);
        f.setValue(domainName);

        QString queryV = "DELETE FROM forwardings WHERE source LIKE '%@" + db.driver()->formatValue(f).mid(1) +  ";";
        qDebug() << "Query: " << queryV;

        if (!query.exec(queryV))
        {
            QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
            return;
        }
    }

    if (1)
    {
        QSqlField f;
        f.setType(QVariant::String);
        f.setValue(domainName);

        QString queryV = "DELETE FROM forwardings WHERE destination LIKE '%@" + db.driver()->formatValue(f).mid(1) +  ";";
        qDebug() << "Query: " << queryV;

        if (!query.exec(queryV))
        {
            QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
            return;
        }
    }

    QMessageBox::information(this, windowTitle(), "Domain " + domainName +  " and accounts registries successfully removed");

    delete item;

}
