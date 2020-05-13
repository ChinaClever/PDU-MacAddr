/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "datapacket.h"

sDataPacket::sDataPacket()
{
    macs = new sMacAddrs;
    initData();
}

sDataPacket *sDataPacket::bulid()
{
    static sDataPacket* sington = nullptr;
    if(sington == nullptr)
        sington = new sDataPacket();
    return sington;
}

void sDataPacket::initData()
{
    initIEEE();
    initIp();
    initMpdu();
    initRpdu();
    initZpdu();
    initAts();
}

void sDataPacket::initIEEE()
{
    sMacUnit *unit = &(macs->IEEE);
    unit->id = 0;
    unit->name = "IEEE";
    unit->start += "30-00-00";
    unit->end += "3F-FF-FF";
}

void sDataPacket::initIp()
{
    sMacUnit *unit = &(macs->IP);
    unit->id = 1;
    unit->name = "IP";
    unit->start += "31-00-00";
    unit->mac += "31-00-01";
    unit->end += "32-FF-FF";
}

void sDataPacket::initMpdu()
{
    sMacUnit *unit = &(macs->MPDU);
    unit->id = 2;
    unit->name = "MPDU";
    unit->start += "33-00-00";
    unit->mac += "33-00-01";
    unit->end += "34-FF-FF";
}

void sDataPacket::initRpdu()
{
    sMacUnit *unit = &(macs->RPDU);
    unit->id = 3;
    unit->name = "RPDU";
    unit->start += "37-00-00";
    unit->mac += "37-00-01";
    unit->end += "38-FF-FF";
}


void sDataPacket::initZpdu()
{
    sMacUnit *unit = &(macs->ZPDU);
    unit->id = 4;
    unit->name = "ZPDU";
    unit->start += "35-00-00";
    unit->mac += "35-00-01";
    unit->end += "36-FF-FF";
}

void sDataPacket::initAts()
{
    sMacUnit *unit = &(macs->ATS);
    unit->id = 5;
    unit->name = "ATS";
    unit->start += "30-00-00";
    unit->mac += "30-00-01";
    unit->end += "30-FF-FF";
}
