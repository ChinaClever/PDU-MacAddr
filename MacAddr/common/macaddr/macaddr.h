#ifndef MACADDR_H
#define MACADDR_H
#include "common.h"
#include "datapacket.h"

class MacAddr
{
    MacAddr();
public:
    static MacAddr *bulid();

    bool isMacAddress(QString mac);
    uint macToInt(QString str);
    QString intToMac(uint v);

protected:
    QByteArray intToByte(uint number);
    QByteArray get_mac_array_from_QString(const QString &in);

private:
    sDataPacket *mPacket;
};

#endif // MACADDR_H
