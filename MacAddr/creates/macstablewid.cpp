/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "macstablewid.h"

MacsTableWid::MacsTableWid(QWidget *parent) : ComTableWid(parent)
{
    initWid();
}


void MacsTableWid::initWid()
{
    QString title = tr("MAC地址列表");
    QStringList header;
    header << tr("MAC地址");
    initTableWid(header, 0, title);
}


void MacsTableWid::appendItem(int id, const sMacUnit &unit)
{
    QStringList listStr;
    //listStr << QString::number(id+1);
    listStr << unit.mac;
    setTableRow(id, listStr);
}


void MacsTableWid::setData(const QList<sMacUnit> &list)
{
    delTable();
    for(int i=0; i<list.size(); ++i) {
        appendItem(i, list.at(i));
    }
}
