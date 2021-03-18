#ifndef CONFIGBASH
#define CONFIGBASH
#include "sysconfigfile.h"
#include "serialport.h"
#include "datapacket.h"

struct sConfigItem
{
    sConfigItem() {logCount = 100*10000;}
    SerialPort *serial; // 串口对象
    uint logCount; // 数据库最大允许的纪录条数
};

class ConfigBase
{
    ConfigBase();
public:
    static ConfigBase *bulid();
    sConfigItem *item;

    QString getSerialName();
    void setSerialName(const QString &name);

    void setMacUnit(sMacUnit *unit);
    void getMacUnit(sMacUnit *unit);

    virtual QString getPrefix(){return "Mac";}
};

#endif // CONFIGBASH
