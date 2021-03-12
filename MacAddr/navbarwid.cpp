/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "navbarwid.h"
#include "ui_navbarwid.h"
#include "backcolourcom.h"
#include <QGridLayout>

NavBarWid::NavBarWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavBarWid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/title_back.jpg");
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 6);
    gridLayout->addWidget(this);
    ui->macBtn->setHidden(true);
}

NavBarWid::~NavBarWid()
{
    delete ui;
}

void NavBarWid::on_macBtn_clicked()
{
    emit navBarSig(0);
}

void NavBarWid::on_batchBtn_clicked()
{
    emit navBarSig(1);
}

void NavBarWid::on_setBtn_clicked()
{
    emit navBarSig(2);
}

void NavBarWid::on_logBtn_clicked()
{
    emit navBarSig(3);
}
