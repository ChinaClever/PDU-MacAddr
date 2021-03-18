/*
 * editusrdlg.cpp
 *  用户信息修改界面
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "maceditdlg.h"

MacEditDlg::MacEditDlg(QWidget *parent) :
    MacNewDlg(parent)
{
    QString str = tr("编辑MAC地址");
    editTitle(str);
}

MacEditDlg::~MacEditDlg()
{
}


void MacEditDlg::setId(int id)
{
    mId = id;
    sMacItem it = DbMacs::bulid()->findById(id);
    loadInfo(it);
}


bool MacEditDlg::saveInfo(sMacItem &it)
{
    it.id = mId;
    return DbMacs::bulid()->updateItem(it);
}
