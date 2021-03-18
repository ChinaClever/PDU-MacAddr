/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "datapacket.h"
#include "configbase.h"

sDataPacket::sDataPacket()
{
    mac = new sMacUnit;
    initMac();
}

sDataPacket *sDataPacket::bulid()
{
    static sDataPacket* sington = nullptr;
    if(sington == nullptr)
        sington = new sDataPacket();
    return sington;
}


void sDataPacket::initMac()
{
    sMacUnit *unit = mac;
    unit->id = 0;
    unit->name = "IP-PDU";
    unit->start += "30:00:00";
    unit->mac += "30:00:00";
    unit->end += "3F:FF:FF";
    unit->pwd = "123456";
    unit->dir = "D:";
    ConfigBase::bulid()->getMacUnit(unit);
}
