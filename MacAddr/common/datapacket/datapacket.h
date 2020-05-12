#ifndef DATAPACKET_H
#define DATAPACKET_H
#include <QtCore>
#include <QColor>



struct IEEE
{
    IEEE() {
        value = "2C-26-5F-";
        start = "30-00-00";
        end = "3F-FF-FF";
    }

    QString value;
    QString start;
    QString end;
};

/**
 * 数据包
 */
class sDataPacket
{
    sDataPacket();
public:
    static sDataPacket *bulid();

    IEEE ie;
};



#endif // DATAPACKET_H
