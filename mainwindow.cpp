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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

#include "dialog_domains.h"

#include "dialog_addserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    popFromConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::popFromConfig()
{
    QSettings settings;
    serversCFG.clear();
    int size = settings.beginReadArray("servers");
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        serverParams x;

        x.serverName = settings.value("serverName").toString();
        x.dbhost     = settings.value("dbhost").toString();
        x.port       = settings.value("port").toUInt();
        x.user       = settings.value("username").toString();
        x.pass       = settings.value("password").toString();
        x.dbname     = settings.value("dbname").toString();

        serversCFG.insert(x);
    }
    settings.endArray();
    // Load into icons
    serversCFG2GUI();
}

void MainWindow::serversCFG2GUI()
{
    ui->listWidget_servers->clear();
    foreach(serverParams x, serversCFG)
    {
        QListWidgetItem * item = new QListWidgetItem(ui->listWidget_servers);
        item->setIcon(QIcon("://icons/data_storage.svg"));
        item->setText(x.serverName);
    }
}

void MainWindow::pushToConfig()
{
    QSettings settings;
    settings.beginWriteArray("servers");
    unsigned int i=0;
    foreach (serverParams x, serversCFG)
    {
        settings.setArrayIndex(i++);
        settings.setValue("serverName", x.serverName);
        settings.setValue("dbhost",     x.dbhost);
        settings.setValue("port",       x.port);
        settings.setValue("username",   x.user);
        settings.setValue("password",   x.pass);
        settings.setValue("dbname",     x.dbname);
    }
    settings.endArray();
}

void MainWindow::on_listWidget_servers_itemDoubleClicked(QListWidgetItem *item)
{
    // CONNECT:
    if (!item)
    {
        QMessageBox::warning(this,"Connect Item","Please select an item before.");
        return;
    }

    serverParams x;
    x.serverName = ui->listWidget_servers->currentItem()->text();
    x = *serversCFG.find(x);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "db");
    db.setConnectOptions("connect_timeout=5");
    db.setHostName(x.dbhost);
    db.setDatabaseName(x.dbname);
    db.setUserName(x.user);
    db.setPassword(x.pass);
    db.setPort(x.port);

    bool ok = db.open();

    qDebug() << "drivers: "<< QSqlDatabase::drivers();

    if (!ok)
    {
        QMessageBox::critical(this,"Database Connection",db.lastError().text());
        qDebug() << "Failed to connect to: " << x.dbhost;
    }
    else
    {
        hide();
        Dialog_Domains domains;
        domains.exec();
        show();
    }
}

void MainWindow::on_actionAddServer_triggered()
{
    // ADD Server:
    Dialog_AddServer addServerDlg;
    while (addServerDlg.exec())
    {
        serverParams x = addServerDlg.getServerParams();

        if (x.dbhost.isEmpty()) QMessageBox::warning(this,"Add Item","Choose a database hostname.");
        else if (x.dbname.isEmpty()) QMessageBox::warning(this,"Add Item","Choose a database name.");
        else if (x.user.isEmpty()) QMessageBox::warning(this,"Add Item","Choose a database user.");
        else if (x.serverName.isEmpty()) QMessageBox::warning(this,"Add Item","Choose a server name.");
        else if ( serversCFG.find(x) != serversCFG.end())
        {
            QMessageBox::warning(this,"Add Item","Choose another server name.");
        }
        else
        {
            serversCFG.insert(x);
            pushToConfig();
            serversCFG2GUI();
            break;
        }
    }
}

void MainWindow::on_actionRemoveServer_triggered()
{
    // REMOVE Server:
    if (!ui->listWidget_servers->currentItem())
    {
        QMessageBox::warning(this,"Remove Item","Please select an item before.");
        return;
    }
    serverParams x;
    x.serverName = ui->listWidget_servers->currentItem()->text();
    serversCFG.remove(x);
    delete ui->listWidget_servers->currentItem();
    pushToConfig();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About doveMailAdmin",
                       "  This is a little program to organize your emails in\n"
                       "  your private email server (dovecot+postfix+mysql based)\n"
                       "\n"
                       "  If you need support or any new features please feel free\n"
                       " to contact me.\n"
                       "\n"
                       "  Telegram: @unmanarc\n"
                       "  Email:    aaron@unmanarc.com\n"
                       "  Github:   /unmanarc\n"
                       "  Web:      https://www.unmanarc.com/\n"
                       );
}
