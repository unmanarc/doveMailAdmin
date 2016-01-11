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
#include "dialog_users.h"
#include "ui_dialog_users.h"

#include <QDebug>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlError>
#include <QMessageBox>

#include "qssha256.h"
#include "dialog_users_addforwarding.h"
#include "dialog_changepassword.h"
#include "dialog_users_add.h"

Dialog_Users::Dialog_Users(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Users)
{
    ui->setupUi(this);
}

void Dialog_Users::setCurrentDomain(const QString &domain)
{
    ui->lineEdit_domain->setText(domain);
}

Dialog_Users::~Dialog_Users()
{
    delete ui;
}

void Dialog_Users::showEvent(QShowEvent *event)
{
    refreshUserList();
}

QTreeWidgetItem *Dialog_Users::createNewUserAtGUI(QString email)
{
    QTreeWidgetItem * item = new QTreeWidgetItem(ui->treeWidget_users);
    item->setIcon(0, QIcon("://icons/mail.svg"));
    item->setText(0, email);
    return item;
}
QTreeWidgetItem *Dialog_Users::createNewForwardingAtGUI(QString email, QTreeWidgetItem *parent)
{
    QTreeWidgetItem * item = new QTreeWidgetItem(parent);
    item->setIcon(0, QIcon("://icons/forward.svg"));
    item->setText(0, email);
    return item;
}

void Dialog_Users::refreshUserList()
{
    QStringList emails = getDomainUsers(ui->lineEdit_domain->text());

    ui->treeWidget_users->clear();
    for (const QString & email : emails)
    {
        QTreeWidgetItem * item = createNewUserAtGUI(email);
        QStringList forwardings = getUserForwardings(email);
        for (const QString forwarding :  forwardings)
        {
            createNewForwardingAtGUI(forwarding,item);
        }
    }
}

QStringList Dialog_Users::getDomainUsers(const QString &domainName)
{
    QStringList r;
    QSqlDatabase db = QSqlDatabase::database("db");
    QSqlQuery query(db);

    QSqlField f;
    f.setType(QVariant::String);
    f.setValue(domainName);

    QString queryV = "SELECT email FROM users WHERE email LIKE '%@" + db.driver()->formatValue(f).mid(1) +  ";";
    qDebug() << "Query: " << queryV;

    if (!query.exec(queryV))
    {
        QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
        return r;
    }
    while (query.next())
    {
        r.append(query.value(0).toString());
    }

    return r;
}

QStringList Dialog_Users::getUserForwardings(const QString &userName)
{
    QStringList r;
    QSqlDatabase db = QSqlDatabase::database("db");
    QSqlQuery query(db);
    query.prepare("SELECT source FROM forwardings WHERE destination=?;");
    query.addBindValue(userName);
    if (!query.exec())
    {
        QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
        return r;
    }
    while (query.next())
    {
        r.append(query.value(0).toString());
    }
    return r;
}

void Dialog_Users::on_pushButton_changePassword_clicked()
{
    QTreeWidgetItem * item = ui->treeWidget_users->currentItem();
    if (!item)
    {
        QMessageBox::warning(this,windowTitle(), "Please select an item before.");
        return;
    }
    else if (item->parent())
    {
        QMessageBox::warning(this,windowTitle(), "Please select an user item before (not forwarding).");
        return;
    }

    Dialog_ChangePassword changePassword;

    if (changePassword.exec())
    {
        QSSHA256 sshagen;
        QString sshaPW = sshagen.genSSHA256Password(changePassword.getPassword());

        QSqlDatabase db = QSqlDatabase::database("db");
        QSqlQuery query(db);
        query.prepare("UPDATE users SET password=? WHERE email=?;");
        query.addBindValue(sshaPW);
        query.addBindValue(item->text(0));
        if (!query.exec())
        {
            QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
        }
        else
        {
            QMessageBox::information(this,"Change Password", "Password Changed.");
        }
    }
}

void Dialog_Users::on_pushButton_addForwarding_clicked()
{
    QTreeWidgetItem * item = ui->treeWidget_users->currentItem();
    if (!item)
    {
        QMessageBox::warning(this,windowTitle(), "Please select an item before.");
        return;
    }
    else if (item->parent())
    {
        QMessageBox::warning(this,windowTitle(), "Please select an user item before (not a forwarding one).");
        return;
    }


    Dialog_Users_AddForwarding usersAddFwd;
    usersAddFwd.setDestination(item->text(0));
    if (usersAddFwd.exec())
    {
        QSqlDatabase db = QSqlDatabase::database("db");
        QSqlQuery query(db);
        query.prepare("INSERT INTO forwardings(`source`,`destination`) VALUES(?,?);");
        query.addBindValue(usersAddFwd.getSource());
        query.addBindValue(item->text(0));
        if (!query.exec())
        {
            QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
        }
        else
        {
            createNewForwardingAtGUI(usersAddFwd.getSource(),item);
            QMessageBox::information(this, windowTitle(),  usersAddFwd.getSource() + " Forwarding successfully created.");
        }
    }
}

void Dialog_Users::on_pushButton_addNewUser_clicked()
{
    Dialog_Users_Add addUser;
    addUser.setDomain(ui->lineEdit_domain->text());
    if (addUser.exec())
    {
        QSSHA256 sshagen;

        QString email = addUser.getUserName() + "@" + ui->lineEdit_domain->text();
        QString sshaPW = sshagen.genSSHA256Password(addUser.getPassword());

        QSqlDatabase db = QSqlDatabase::database("db");
        QSqlQuery query(db);
        query.prepare("INSERT INTO users(`email`,`password`) VALUES(?,?);");
        query.addBindValue(email);
        query.addBindValue(sshaPW);
        if (!query.exec())
        {
            QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
        }
        else
        {
            createNewUserAtGUI(email);
            QMessageBox::information(this, windowTitle(),  email + " Successfully created.");
        }
    }
}

void Dialog_Users::on_pushButton_remove_clicked()
{
    QTreeWidgetItem * item = ui->treeWidget_users->currentItem();
    if (!item)
    {
        QMessageBox::warning(this,windowTitle(), "Please select an item before.");
        return;
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, windowTitle(), "Remove " + item->text(0) + "?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No)
        {
            QMessageBox::information(this, windowTitle(), "Aborted");
            return;
        }

        if (item->parent())
        {
            // Removing a forwarding...
            QSqlDatabase db = QSqlDatabase::database("db");
            QSqlQuery query(db);
            query.prepare("DELETE FROM forwardings WHERE source=?;");
            query.addBindValue(item->text(0));
            if (!query.exec())
            {
                QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
            }
            else delete item;
        }
        else if (!item->parent())
        {
            // Removing a user
            QString email = item->text(0);
            QSqlDatabase db = QSqlDatabase::database("db");
            if (1)
            {
                QSqlQuery query(db);
                query.prepare("DELETE FROM users WHERE email=?;");
                query.addBindValue(email);
                if (!query.exec())
                {
                    QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
                }
                else delete item;
            }
            if (1)
            {
                QSqlQuery query(db);
                query.prepare("DELETE FROM forwardings WHERE destination=?;");
                query.addBindValue(email);
                if (!query.exec())
                {
                    QMessageBox::warning(this, tr("Error"), tr("Error executing query: ") + query.lastError().text());
                }
            }
        }
    }
}

