#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QtCore>
#include <QColor>

#define MAC_ADDR_PREFIX "2C-26-5F-"

struct sMacUnit
{
    sMacUnit() {
        used=value=counts=0;
        mac = start = end=prefixs = MAC_ADDR_PREFIX;
    }

    uint id;
    QString name;
    QString prefixs;
    QString mac;
    QString start;
    QString end;
    uint value;
    uint counts;
    uint used;
};


struct sMacAddrs
{
    sMacAddrs() {}

    sMacUnit IEEE;
    sMacUnit IP;
    sMacUnit MPDU;
    sMacUnit ZPDU;
    sMacUnit RPDU;
    sMacUnit ATS;
};

/**
 * 数据包
 */
class sDataPacket
{
    sDataPacket();
public:
    static sDataPacket *bulid();
    sMacAddrs  *macs;

protected:
    void initData();
    void initIEEE();
    void initIp();
    void initMpdu();
    void initRpdu();
    void initZpdu();
    void initAts();
};



#endif // DATAPACKET_H
