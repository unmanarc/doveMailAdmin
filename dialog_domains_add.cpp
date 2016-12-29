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
#include "dialog_domains_add.h"
#include "ui_dialog_domains_add.h"

Dialog_Domains_Add::Dialog_Domains_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Domains_Add)
{
    ui->setupUi(this);
    ui->lineEdit_domainName->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9\\.\\-\\_\\?]*$"), this));
}

Dialog_Domains_Add::~Dialog_Domains_Add()
{
    delete ui;
}

QString Dialog_Domains_Add::getDomain()
{
    return ui->lineEdit_domainName->text();
}
