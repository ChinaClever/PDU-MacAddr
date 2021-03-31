/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
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
    groupBox_background_icon(this);
    on_typeBox_currentIndexChanged(0);
    ui->groupBox_1->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
    ui->pwdEdit->setText(mUnit->pwd);
    ui->passwordEdit->setText(mUnit->pwd);

    QDate buildDate = QLocale(QLocale::English ).toDate( QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");
    ui->VerBtn->setText(QString("V0.6\n%1").arg(buildDate.toString("yyyy-MM-dd")));
}


void SettingWid::setWid(sMacUnit *unit)
{
    ui->macEdit->setText(unit->mac);
    ui->startEdit->setText(unit->start);
    ui->endEdit->setText(unit->end);
    ui->spinBox->setValue(unit->cnt);

    MacAddr::bulid()->macHasCounts(*unit);
    ui->countEdit->setText(QString::number(unit->counts));

    MacAddr::bulid()->macUsedCounts(*unit);
    ui->usedEdit->setText(QString::number(unit->used));
}


void SettingWid::on_typeBox_currentIndexChanged(int)
{
    sMacUnit *unit = sDataPacket::bulid()->mac;
    setWid(unit);
    mUnit = unit;
}

bool SettingWid::authorityVerification()
{
    bool ok, ret = false;
    QString text = QInputDialog::getText(this,tr("口令验证"),tr("请输入管理员密码"), QLineEdit::Password,NULL,&ok);
    if(ok && !text.isEmpty()) {
        if(text == mUnit->pwd) ret = true;
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

    mUnit->cnt = ui->spinBox->value();
    QString pwd = ui->pwdEdit->text();
    if(pwd.isEmpty()) {
        CriticalMsgBox box(this, tr("授权密码不能为空，请重新输入！\n"));
        return false;
    } else if(pwd == ui->passwordEdit->text()) {
        mUnit->pwd = pwd;
    } else {
        CriticalMsgBox box(this, tr("二次密码输入不一致，请重新输入！\n"));
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
    bool en = false;
    static int isRun = 0;
    if(isRun % 2) {
        if(inputCheck()) {
            isRun++;
            saveLog(mUnit);
            ui->btn->setText(tr("修改"));
        }
    } else {
        bool ret = authorityVerification();
        if(ret) {
            isRun++;
            en = true;
            ui->btn->setText(tr("保存"));
        } else {
            CriticalMsgBox box(this, tr("身份验证错误\n"));
        }
    }
    ui->groupBox_1->setEnabled(en);
    ui->groupBox_2->setEnabled(en);
}

void SettingWid::on_readMeBtn_clicked()
{
    ReadMeDlg dlg(this);
    dlg.exec();
}
