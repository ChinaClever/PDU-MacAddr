/*
 * common.cpp
 * 公共方法接口
 *
 *  Created on: 2018年1月1日
 *      Author: Lzy
 */
#include "common.h"
#include <QWidget>
#include <QHeaderView>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <QApplication>



void cm_ClipBoardSet(const QString &str)
{
    QClipboard *board = QApplication::clipboard();//使用 QApplication::clipboard() 函数获得系统剪贴板对象。这个函数的返回值是 QClipboard 指针。
    board->setText(str); //通过 setText()，setImage() 或者 setPixmap() 函数可以将数据放置到剪贴板内，也就是通常所说的剪贴或者复制的操作；
}

QString cm_ClipBoardGet()
{
    QClipboard *board = QApplication::clipboard();
    return board->text(); //使用text()，image() 或者 pixmap() 函数则可以从剪贴板获得数据，也就是粘贴
}

/***
  *判断一个字符串是否为纯数字
  */
bool cm_isDigitStr(const QString &src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
    const char *s = ba.data();

    while(*s && *s>='0' && *s<='9') s++;

    if (*s) //不是纯数字
        return false;

    return true;
}

/**
 * @brief 是否为IP地址
 * @param ip
 * @return
 */
bool cm_isIPaddress(const QString& ip)
{
    QRegExp regExp("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    if(regExp.exactMatch(ip))
        return true ;

    return false;
}


/**
 * @brief 转16进制
 * @param array
 * @return
 */
QString cm_ByteArrayToHexStr(const QByteArray &array)
{
    QString strArray = array.toHex().toUpper(); // 十六进制
    for(int i=0; i<array.size(); ++i)
        strArray.insert(2+3*i, ' '); // 插入空格
    return strArray;
}

/**
 * @brief 转十进制
 * @param array
 * @return
 */
QString cm_ByteArrayToUcharStr(const QByteArray &array)
{
    QString strArray ;
    for(int i=0; i<array.size(); ++i)
        strArray += QString::number((uchar)array.at(i)) + " ";  // 十进制
    return strArray;
}



