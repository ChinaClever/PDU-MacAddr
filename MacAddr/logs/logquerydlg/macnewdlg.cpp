/*
 * newusrdlg.cpp
 *  用户增加界面
 *  新用户信息增加
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "macnewdlg.h"
#include "ui_macnewdlg.h"


MacNewDlg::MacNewDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MacNewDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
}

MacNewDlg::~MacNewDlg()
{
    delete ui;
}

/**
 * @brief 修改标题
 * @param str
 */
void MacNewDlg::editTitle(const QString &str)
{
    ui->titlelabel->setText(str);
    this->setWindowTitle(str);
}



/**
 * @brief 用户信息加载
 * @param usr
 */
void MacNewDlg::loadInfo(sMacItem &it)
{
    ui->nameEdit->setText(it.user);
    ui->snEdit->setText(it.sn);
    ui->macEdit->setText(it.mac);
    ui->typeBox->setCurrentText(it.dev);
}


/**
 * @brief 输入信息检查
 * @return
 */
bool MacNewDlg::informationCheck(void)
{
    QString str = ui->nameEdit->text();
    if(str.isEmpty()) {
        InfoMsgBox(this, tr("客户名称不能为空"));
        return false;
    }

    str = ui->macEdit->text();
    bool ret = MacAddr::bulid()->isMacAddress(str);
    if(!ret) {
        InfoMsgBox(this,  tr("MAC地址格式错误！"));
        return false;
    }

   return ret;
}


bool MacNewDlg::saveInfo(sMacItem &it)
{
    DbMacs* db = DbMacs::bulid();
    int rtn = db->contains(it.mac);
    if(rtn > 0) return false;

    return db->insertItem(it);
}

void MacNewDlg::on_saveBtn_clicked()
{
    if(informationCheck())
    {
        sMacItem it;
        it.dev = ui->typeBox->currentText();
        it.user = ui->nameEdit->text();
        it.sn = ui->snEdit->text();
        it.mac = ui->macEdit->text();
        if(saveInfo(it))
            accept();
        else
            InfoMsgBox(this,  tr("账号已存在"));
    }
}
