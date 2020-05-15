#include "settingwid.h"
#include "ui_settingwid.h"
#include "readmedlg.h"

SettingWid::SettingWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWid)
{
    ui->setupUi(this);
    initWid();
}

SettingWid::~SettingWid()
{
    delete ui;
}

void SettingWid::initWid()
{
    sMacUnit unit = sDataPacket::bulid()->macs->IEEE;
    ui->ieStartEdit->setText(unit.start);
    ui->ieEndEdit->setText(unit.end);

    groupBox_background_icon(this);
    on_typeBox_currentIndexChanged(0);
    ui->groupBox->setEnabled(false);
}


void SettingWid::setWid(sMacUnit *unit)
{
    ui->macEdit->setText(unit->mac);
    ui->startEdit->setText(unit->start);
    ui->endEdit->setText(unit->end);

    MacAddr::bulid()->macHasCounts(*unit);
    ui->countEdit->setText(QString::number(unit->counts));

    MacAddr::bulid()->macUsedCounts(*unit);
    ui->usedEdit->setText(QString::number(unit->used));
}


void SettingWid::on_typeBox_currentIndexChanged(int index)
{
    sMacUnit *unit = nullptr;
    sMacAddrs *macs = sDataPacket::bulid()->macs;
    switch (index) {
    case 0:  unit = &(macs->IP); break;
    case 1:  unit = &(macs->MPDU); break;
    case 2:  unit = &(macs->RPDU); break;
    case 3:  unit = &(macs->ZPDU); break;
    case 4:  unit = &(macs->ATS); break;
    }
    setWid(unit);
    mUnit = unit;
}

bool SettingWid::authorityVerification()
{
    bool ok, ret = false;
    QString text = QInputDialog::getText(this,tr("口令验证"),tr("请输入管理员密码"), QLineEdit::Normal,NULL,&ok);
    if(ok && !text.isEmpty()) {
        if(text == "123456") ret = true;
    }

    return ret;
}

bool SettingWid::inputCheck()
{
    MacAddr *m = MacAddr::bulid();
    QString str = ui->macEdit->text();
    bool ret = m->isMacAddress(str);
    if(ret) {
        mUnit->mac = str;
    } else {
        CriticalMsgBox box(this, tr("当前MAC地址格式错误，请重新输入！\n"));
        return false;
    }

    str = ui->startEdit->text();
    ret = m->isMacAddress(str);
    if(ret) {
        mUnit->start = str;
    } else {
        CriticalMsgBox box(this, tr("起始MAC地址格式错误，请重新输入！\n"));
        return false;
    }

    str = ui->endEdit->text();
    ret = m->isMacAddress(str);
    if(ret) {
        mUnit->end = str;
    } else {
        CriticalMsgBox box(this, tr("结束MAC地址格式错误，请重新输入！\n"));
        return false;
    }

    return true;
}

void SettingWid::saveLog(sMacUnit *unit)
{
    setWid(unit);
    ConfigBase::bulid()->setMacUnit(unit);
}

void SettingWid::on_btn_clicked()
{
    static int isRun = 0;
    if(isRun % 2) {
        if(inputCheck()) {
            isRun++;
            saveLog(mUnit);
            ui->btn->setText(tr("修改"));
            ui->groupBox->setEnabled(false);
        }
    } else {
        bool ret = authorityVerification();
        if(ret) {
            isRun++;
            ui->btn->setText(tr("保存"));
            ui->groupBox->setEnabled(true);
        } else {
            CriticalMsgBox box(this, tr("身份验证错误\n"));
        }
    }
}

void SettingWid::on_readMeBtn_clicked()
{
    ReadMeDlg dlg(this);
    dlg.exec();
}
