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
#include "dialog_users_add.h"
#include "ui_dialog_users_add.h"

#include <QMessageBox>

Dialog_Users_Add::Dialog_Users_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Users_Add)
{
    ui->setupUi(this);
    ui->lineEdit_userName->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9\\.\\-\\_\\?]*$"), this));
}

Dialog_Users_Add::~Dialog_Users_Add()
{
    delete ui;
}

void Dialog_Users_Add::setDomain(const QString &domainName)
{
    ui->label_domain->setText(domainName);
}

void Dialog_Users_Add::accept()
{
    if (ui->lineEdit_userName->text().isEmpty())
    {
        QMessageBox::critical(this,windowTitle(),"User/Email is empty");
        ui->lineEdit_userName->setFocus();
    }
    else if (ui->lineEdit_password_1->text() != ui->lineEdit_password_2->text())
    {
        QMessageBox::critical(this,windowTitle(),"Password does not match");
        ui->lineEdit_password_2->setFocus();
    }
    else if (ui->lineEdit_password_1->text().isEmpty())
    {
        QMessageBox::critical(this,windowTitle(),"Password is empty");
        ui->lineEdit_password_1->setFocus();
    }
    else
    {
        QDialog::accept();
    }
}

QString Dialog_Users_Add::getUserName()
{
    return ui->lineEdit_userName->text();
}

QString Dialog_Users_Add::getPassword()
{
    return ui->lineEdit_password_1->text();
}
