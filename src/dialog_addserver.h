#ifndef DIALOG_ADDSERVER_H
#define DIALOG_ADDSERVER_H

#include <QDialog>
#include "serverparams.h"

namespace Ui {
class Dialog_AddServer;
}

class Dialog_AddServer : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_AddServer(QWidget *parent = 0);
    ~Dialog_AddServer();
    serverParams getServerParams();

private:
    Ui::Dialog_AddServer *ui;
};

#endif // DIALOG_ADDSERVER_H
