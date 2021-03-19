/*
 * 配置文件公共基类
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "configbase.h"

ConfigBase::ConfigBase()
{
    item = new sConfigItem();
    item->serial = nullptr;
}

ConfigBase *ConfigBase::bulid()
{
    static ConfigBase* sington = nullptr;
    if(sington == nullptr)
        sington = new ConfigBase();
    return sington;
}


/**
 * @brief 获取串口名称
 * @return 串口名
 */
QString ConfigBase::getSerialName()
{
    QString prefix = getPrefix();
    QString str = QString("%1_COM").arg(prefix);
    return com_cfg_readStr(str, prefix);
}

/**
 * @brief 设置串口名
 * @param name
 */
void ConfigBase::setSerialName(const QString &name)
{
    QString prefix = getPrefix();
    QString str = QString("%1_COM").arg(prefix);
    com_cfg_write(str, name, prefix);
}


void ConfigBase::setMacUnit(sMacUnit *unit)
{
    QString prefix = getPrefix();
    QString str = QString("mac");
    com_cfg_write(str, unit->mac, prefix);

    str = QString("start");
    com_cfg_write(str, unit->start, prefix);

    str = QString("end");
    com_cfg_write(str, unit->end, prefix);
    com_cfg_write("cnt", QString::number(unit->cnt), prefix);

    com_cfg_write("pwd", unit->pwd, "Sys");
    com_cfg_write("dir", unit->dir, "Sys");
}


void ConfigBase::getMacUnit(sMacUnit *unit)
{
    QString prefix = getPrefix();
    QString str = QString("mac");
    QString res = com_cfg_readStr(str, prefix);
    if(!res.isEmpty()) unit->mac = res;

    str = QString("start");
    res = com_cfg_readStr(str, prefix);
    if(!res.isEmpty()) unit->start = res;

    str = QString("end");
    res = com_cfg_readStr(str, prefix);
    if(!res.isEmpty()) unit->end = res;

    str = QString("cnt");
    int cnt = com_cfg_readInt(str, prefix);
    if(cnt > 0) unit->cnt = cnt;

    res = com_cfg_readStr("pwd", "Sys");
    if(!res.isEmpty()) unit->pwd = res;

    res = com_cfg_readStr("dir", "Sys");
    if(!res.isEmpty()) unit->dir = res;
}
