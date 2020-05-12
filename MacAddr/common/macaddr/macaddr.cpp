#include "macaddr.h"

MacAddr::MacAddr()
{
    mPacket = sDataPacket::bulid();
}


MacAddr *MacAddr::bulid()
{
    static MacAddr* sington = nullptr;
    if(sington == nullptr)
        sington = new MacAddr();
    return sington;
}


uint MacAddr::macToInt(QString str)
{
    bool ok;
    str = str.replace(mPacket->ie.value, QString(""));
    str = str.replace(QString("-"), QString(""));
    uint ret = str.toUInt(&ok, 16);
    if(!ok) ret = 0;

    return ret;
}

QByteArray MacAddr::intToByte(uint number)
{
    QByteArray abyte0;
    abyte0.resize(3);
    abyte0[2] = (uchar)  (0x000000ff & number);
    abyte0[1] = (uchar) ((0x0000ff00 & number) >> 8);
    abyte0[0] = (uchar) ((0x00ff0000 & number) >> 16);
    return abyte0;
}



QString MacAddr::intToMac(uint v)
{
    QByteArray array = intToByte(v);
    QString str = cm_ByteArrayToHexStr(array);
    QString mac = mPacket->ie.value + str.left(str.size()-1);
    return mac.replace(QString(" "), QString("-"));
}



/**
* 函数功能:将格式如"EA-EB-EC-AA-AB-AC"的MAC QString字符串转换成6字节的数组，
* 数组的元素对应为{0xEA,0xEB,0xEC,0xAA,0xAB,0xAC}
*/
QByteArray MacAddr::get_mac_array_from_QString(const QString &in)
{
    QByteArray array;
    unsigned char out[6];
    uint8_t next_ip_separate_symbol_index = 0;
    uint8_t now_ip_separate_symbol_index = 0;

    for(uint8_t i=0;i<6;i++){
        next_ip_separate_symbol_index = (i!=5)? (in.indexOf("-",next_ip_separate_symbol_index+1)):(in.length());
        if((next_ip_separate_symbol_index-now_ip_separate_symbol_index>0)&&(next_ip_separate_symbol_index-now_ip_separate_symbol_index<= 3)){
            *(out+i) = in.mid((i==0)? now_ip_separate_symbol_index:(now_ip_separate_symbol_index+1), \
                              (i==0)? next_ip_separate_symbol_index: \
                                      (next_ip_separate_symbol_index-now_ip_separate_symbol_index-1)).toInt(0,16);
            now_ip_separate_symbol_index = next_ip_separate_symbol_index;
        }else{
            return array;
        }
    }

    array.resize(sizeof(out));//重置数据大小
    memcpy(array.data(), out, sizeof(out));//copy数据

    return array;
}

bool MacAddr::isMacAddress(QString mac)
{
    QRegExp rx("^([A-Fa-f0-9]{2}[-,:]){5}[A-Fa-f0-9]{2}$");
    QRegExpValidator v(rx, 0);
    int pos = 0;
    if(v.validate(mac, pos) == QValidator::Acceptable)
        return true;

    return false;
}
