/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "readmedlg.h"
#include "ui_readmedlg.h"
#include <QtCore>
#include "common.h"

ReadMeDlg::ReadMeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadMeDlg)
{
    ui->setupUi(this);
    initText();
    groupBox_background_icon(this);
}

ReadMeDlg::~ReadMeDlg()
{
    delete ui;
}

void ReadMeDlg::initText()
{
    QFile file("readme.txt");
    bool ret = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(ret) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            ui->textEdit->append(line);
        }
    } else {
        qDebug() << "open readme.txt err";
    }
}

void ReadMeDlg::on_okBtn_clicked()
{
    this->close();
}
