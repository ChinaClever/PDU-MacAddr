#include "createmacwid.h"
#include "ui_createmacwid.h"

CreateMacWid::CreateMacWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateMacWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    on_typeBox_currentIndexChanged(0);
    ui->revokeBtn->setEnabled(false);
}

CreateMacWid::~CreateMacWid()
{
    delete ui;
}

void CreateMacWid::setWid(sMacUnit *unit)
{
    ui->macEdit->setText(unit->mac);
    ui->startEdit->setText(unit->start);
    ui->endEdit->setText(unit->end);
    MacAddr::bulid()->macHasCounts(*unit);
    ui->countEdit->setText(QString::number(unit->counts));
}


void CreateMacWid::on_typeBox_currentIndexChanged(int index)
{
    sMacUnit *unit = sDataPacket::bulid()->mac;
    unit->name = ui->typeBox->currentText();
    unit->id = index;
    setWid(unit);
    mUnit = unit;
    ui->revokeBtn->setEnabled(false);
}

void CreateMacWid::on_copyBtn_clicked()
{
    QString str = ui->macEdit->text();
    if(!str.isEmpty()) {
        cm_ClipBoardSet(str);
        InfoMsgBox box(this,tr("MAC地址：%1，已复制!").arg(str));
    }
}

bool CreateMacWid::inputCheck()
{
    QString str = ui->nameEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("客户名称不能为空，请重新输入！\n"));
        return false;
    }

    return true;
}

void CreateMacWid::saveLog(sMacUnit *unit)
{
    sMacItem item;
    item.dev = ui->typeBox->currentText();
    item.user = ui->nameEdit->text();
    item.sn = ui->snEdit->text();
    item.mac = unit->mac;
    DbMacs::bulid()->insertItem(item);
    ConfigBase::bulid()->setMacUnit(unit);
}

void CreateMacWid::on_createBtn_clicked()
{
    if(!inputCheck()) return;
    bool ret = MacAddr::bulid()->createMac(*mUnit);
    if(ret) {
        setWid(mUnit);
        saveLog(mUnit);
        on_copyBtn_clicked();
        ui->revokeBtn->setEnabled(true);
    } else {
        CriticalMsgBox box(this, tr("创建失败"));
    }
}

void CreateMacWid::on_revokeBtn_clicked()
{
    QuMsgBox box(this, tr("请确认是否撤销？"));
    if(box.Exec()) {
        QString mac = mUnit->mac;
        bool ret = MacAddr::bulid()->revokeMac(*mUnit);
        if(ret) {
            setWid(mUnit);
            DbMacs::bulid()->removeMac(mac);
            ui->revokeBtn->setEnabled(false);
            ConfigBase::bulid()->setMacUnit(mUnit);
        }
    }
}
