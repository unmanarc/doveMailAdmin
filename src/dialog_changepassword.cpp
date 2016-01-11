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
#include "dialog_changepassword.h"
#include "ui_dialog_changepassword.h"

#include <QMessageBox>

Dialog_ChangePassword::Dialog_ChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ChangePassword)
{
    ui->setupUi(this);
}

Dialog_ChangePassword::~Dialog_ChangePassword()
{
    delete ui;
}

void Dialog_ChangePassword::accept()
{
    if (ui->lineEdit_password_1->text() != ui->lineEdit_password_2->text())
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

QString Dialog_ChangePassword::getPassword()
{
    return ui->lineEdit_password_1->text();
}
