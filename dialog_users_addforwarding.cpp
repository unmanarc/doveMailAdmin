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
#include "dialog_users_addforwarding.h"
#include "ui_dialog_users_addforwarding.h"

#include <QMessageBox>

Dialog_Users_AddForwarding::Dialog_Users_AddForwarding(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Users_AddForwarding)
{
    ui->setupUi(this);
    QRegExp mailrx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailrx.setCaseSensitivity(Qt::CaseInsensitive);
    mailrx.setPatternSyntax(QRegExp::RegExp);
    ui->lineEdit_from->setValidator(new QRegExpValidator(mailrx, this));
}

Dialog_Users_AddForwarding::~Dialog_Users_AddForwarding()
{
    delete ui;
}

void Dialog_Users_AddForwarding::setDestination(const QString &to)
{
    ui->label_to->setText(to);
}

void Dialog_Users_AddForwarding::accept()
{
    if (ui->lineEdit_from->text().isEmpty())
    {
        QMessageBox::critical(this,windowTitle(),"From 'email' is empty");
        ui->lineEdit_from->setFocus();
    }
    else
    {
        QDialog::accept();
    }

}

QString Dialog_Users_AddForwarding::getSource()
{
    return ui->lineEdit_from->text();
}
