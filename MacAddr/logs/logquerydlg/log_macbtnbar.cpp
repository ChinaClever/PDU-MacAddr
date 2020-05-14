/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "log_macbtnbar.h"

Log_MacBtnBar::Log_MacBtnBar(QWidget *parent) : LogBtnBar(parent)
{
    setEdit();
    importHidden();
}

void Log_MacBtnBar::addBtn()
{
    MacNewDlg dlg(this);
    dlg.exec();
}


void Log_MacBtnBar::modifyBtn(int id)
{
    MacEditDlg dlg(this);
    dlg.setId(id);
    dlg.exec();
}

