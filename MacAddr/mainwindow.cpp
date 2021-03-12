/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mNavBarWid = new NavBarWid(ui->barWid);
    QTimer::singleShot(5,this,SLOT(initFunSlot())); //延时初始化
    connect(mNavBarWid, SIGNAL(navBarSig(int)), this, SLOT(navBarSlot(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initFunSlot()
{
    initWid();
    navBarSlot(1);
}

void MainWindow::initWid()
{
     mCreateMacWid = new CreateMacWid(ui->stackedWid);
     ui->stackedWid->addWidget(mCreateMacWid);

    mMacListWid = new CreateMacListWid(ui->stackedWid);
    ui->stackedWid->addWidget(mMacListWid);

    mSet = new SettingWid(ui->stackedWid);
    ui->stackedWid->addWidget(mSet);

    mLog = new LogMainWid(ui->stackedWid);
    ui->stackedWid->addWidget(mLog);
}

void MainWindow::navBarSlot(int id)
{
    mSet->refreshWid();
    mMacListWid->refreshWid();
    mCreateMacWid->refreshWid();
    ui->stackedWid->setCurrentIndex(id);
}
