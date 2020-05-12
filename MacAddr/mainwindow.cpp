#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "macaddr.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    MacAddr *mac = MacAddr::bulid();
    QString str = "2C-26-5F-30-A0-01";
    qDebug() << mac->isMacAddress(str);
    uint lzy = mac->macToInt(str) + 0xCC;
    qDebug() << mac->intToMac(lzy);



}

MainWindow::~MainWindow()
{
    delete ui;
}

