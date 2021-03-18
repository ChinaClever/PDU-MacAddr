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

    uint macHasCounts(sMacUnit &unit);
    uint macUsedCounts(sMacUnit &unit);

    bool createMac(sMacUnit &unit);
    bool revokeMac(sMacUnit &unit);

    QList<sMacUnit> createMacList(sMacUnit &unit, int num);
    bool revokeMacList(sMacUnit &it, QList<sMacUnit> &units);

protected:
    QByteArray intToByte(uint number);
    QByteArray get_mac_array_from_QString(const QString &in);

private:
    sMacUnit *mMac;
};

#endif // MACADDR_H
