#ifndef MACSTABLEWID_H
#define MACSTABLEWID_H

#include "comtablewid.h"
#include "createmacwid.h"

class MacsTableWid : public ComTableWid
{
    Q_OBJECT
public:
    explicit MacsTableWid(QWidget *parent = nullptr);

    void clearRows(){delTable();}
    void setData(const QList<sMacUnit> &list);

protected:
    void initWid();
    void appendItem(int id, const sMacUnit &unit);
};

#endif // MACSTABLEWID_H
