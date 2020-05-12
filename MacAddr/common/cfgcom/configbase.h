#ifndef CONFIGBASH
#define CONFIGBASH
#include "sysconfigfile.h"
#include "serialport.h"

struct sConfigItem
{
    sConfigItem() {}
    SerialPort *serial; // 串口对象
};

class ConfigBase
{
    ConfigBase();
public:
    static ConfigBase *bulid();
    sConfigItem *item;

    QString getSerialName();
    void setSerialName(const QString &name);

    virtual QString getPrefix(){return "con";}
};

#endif // CONFIGBASH
