#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QSet>
#include "serverparams.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void popFromConfig();

private slots:
    void on_listWidget_servers_itemDoubleClicked(QListWidgetItem *item);

    void on_actionAddServer_triggered();

    void on_actionRemoveServer_triggered();

    void on_actionAbout_triggered();

private:
    void serversCFG2GUI();
    void pushToConfig();
    QSet<serverParams> serversCFG;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
