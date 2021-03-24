#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QtCore>
#include <QColor>

#define MAC_ADDR_PREFIX "2C:26:5F:"

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
    uint cnt;

    QString pwd;
    QString dir;
};



/**
 * 数据包
 */
class sDataPacket
{
    sDataPacket();
public:
    static sDataPacket *bulid();
    sMacUnit *mac;

protected:
      void initMac();
};



#endif // DATAPACKET_H
