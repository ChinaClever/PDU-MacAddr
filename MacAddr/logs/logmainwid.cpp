/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "logmainwid.h"
#include "ui_logmainwid.h"


LogMainWid::LogMainWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogMainWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    QTimer::singleShot(rand()%50,this,SLOT(initFunSLot()));
}

LogMainWid::~LogMainWid()
{
    delete ui;
}


void LogMainWid::initFunSLot()
{
    mMacLog = new LogComWid(ui->stackedWid);
    mMacLog->initWid(DbMacs::bulid(),new Log_MacBtnBar(),  new Log_MacQueryDlg(this));
    ui->stackedWid->addWidget(mMacLog);
}

void LogMainWid::on_comboBox_currentIndexChanged(int index)
{
    ui->stackedWid->setCurrentIndex(index);
}
