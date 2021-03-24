/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "createmaclistwid.h"
#include "ui_createmaclistwid.h"
#include "sqlexportdlg.h"

CreateMacListWid::CreateMacListWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateMacListWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    on_typeBox_currentIndexChanged(0);
    ui->revokeBtn->setEnabled(false);
    mTableWid = new MacsTableWid(ui->widget);
    ui->revokeBtn->setHidden(true);
    ui->exportBtn->setHidden(true);
}

CreateMacListWid::~CreateMacListWid()
{
    delete ui;
}

void CreateMacListWid::setWid(sMacUnit *unit)
{
    ui->macEdit->setText(unit->mac);
    ui->startEdit->setText(unit->start);
    ui->endEdit->setText(unit->end);
    MacAddr::bulid()->macHasCounts(*unit);
    ui->countEdit->setText(QString::number(unit->counts));
}

void CreateMacListWid::on_typeBox_currentIndexChanged(int index)
{
    sMacUnit *unit = sDataPacket::bulid()->mac;
    unit->name = ui->typeBox->currentText();
    unit->id = index;
    mUnit = unit;
    setWid(unit);
    mList.clear();
    ui->revokeBtn->setEnabled(false);
}

bool CreateMacListWid::inputCheck()
{
    QString str = ui->nameEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("客户名称不能为空，请重新输入！\n"));
        return false;
    }

    if(mUnit->counts < 1) {
        CriticalMsgBox box(this, tr("MAC地址已用完，无法继续使用！\n"));
        return false;
    }

    uint num = ui->spinBox->value();
    if(num < 1) {
        CriticalMsgBox box(this, tr("数量不能为空，请重新输入！\n"));
        return false;
    } else if(num > mUnit->counts) {
        CriticalMsgBox box(this, tr("没有这么多MAC，最多为：%1，请重新输入！\n").arg(mUnit->counts));
        return false;
    }

    if(mUnit->counts < mUnit->cnt) {
        QString str = tr("剩余MAC地址，仅有%1个，请向领导反馈").arg(mUnit->counts);
        InfoMsgBox box(this, str);
    }

    QuMsgBox box(this, tr("请确认是否批量生成？"));
    return box.Exec();
}

void CreateMacListWid::saveLogSlot()
{
    sMacItem item;
    ConfigBase::bulid()->setMacUnit(mUnit);
    item.dev = ui->typeBox->currentText();
    item.user = ui->nameEdit->text();

    Db_Tran db;
    for(int i=0; i<mList.size(); ++i) {
        //item.sn = QString::number(i+1);
        item.mac = mList.at(i).mac;
        DbMacs::bulid()->insertItem(item);
    }

    QTimer::singleShot(rand()%50,this,SLOT(on_exportBtn_clicked()));
}

void CreateMacListWid::revokeLogSlot()
{
    Db_Tran db;
    for(int i=0; i<mList.size(); ++i) {
        QString mac = mList.at(i).mac;
        DbMacs::bulid()->removeMac(mac);
    }

    mList.clear();
    ConfigBase::bulid()->setMacUnit(mUnit);
}


void CreateMacListWid::on_createBtn_clicked()
{
    if(!inputCheck()) return;
    int num = ui->spinBox->value();
    mList = MacAddr::bulid()->createMacList(*mUnit, num);
    if(mList.size()) {
        setWid(mUnit);
        mTableWid->setData(mList);
        ui->revokeBtn->setEnabled(true);
        QTimer::singleShot(rand()%200,this,SLOT(saveLogSlot()));
        //InfoMsgBox box(this, tr("MAC地址已生成！"));
    } else {
        CriticalMsgBox box(this, tr("创建失败"));
    }
}

void CreateMacListWid::on_revokeBtn_clicked()
{
    QuMsgBox box(this, tr("请确认是否撤销？"));
    if(box.Exec()) {
        bool ret = MacAddr::bulid()->revokeMacList(*mUnit, mList);
        if(ret) {
            setWid(mUnit);
            mTableWid->clearRows();
            ui->revokeBtn->setEnabled(false);
            QTimer::singleShot(rand()%150,this,SLOT(revokeLog()));
            InfoMsgBox box(this, tr("MAC地址已撤销！"));
        }
    }
}

void CreateMacListWid::on_exportBtn_clicked()
{
    if(mList.size()) {
        SqlExportDlg dlg(this);
        QList<QStringList> list; // 内容
        QString user = ui->nameEdit->text();
        QString dev = ui->typeBox->currentText();
        for(int i=0; i<mList.size(); ++i) {
            QStringList strs;
            strs << QString::number(i+1) << user << dev << mList.at(i).mac;
            list << strs;
        }

        QString date = QDate::currentDate().toString("yyyy-MM-dd");
        QString fn = user + "_" + dev + "_" + date;
        dlg.init(fn, list);
        dlg.exec();

        ui->nameEdit->clear();
        ui->spinBox->setValue(0);
    } else {
        CriticalMsgBox box(this, tr("没有数据无法导出！\n"));
    }
}
