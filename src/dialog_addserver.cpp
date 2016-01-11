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
#include "dialog_addserver.h"
#include "ui_dialog_addserver.h"

Dialog_AddServer::Dialog_AddServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_AddServer)
{
    ui->setupUi(this);
}

Dialog_AddServer::~Dialog_AddServer()
{
    delete ui;
}

serverParams Dialog_AddServer::getServerParams()
{
    serverParams x;
    x.dbhost = ui->lineEdit_hostname->text();
    x.dbname = ui->lineEdit_dbname->text();
    x.port = ui->spinBox_port->value();
    x.user = ui->lineEdit_username->text();
    x.pass = ui->lineEdit_password->text();
    x.serverName = ui->lineEdit_serverName->text();
    return x;
}
