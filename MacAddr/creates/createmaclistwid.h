#ifndef CREATEMACLISTWID_H
#define CREATEMACLISTWID_H

#include "macstablewid.h"

namespace Ui {
class CreateMacListWid;
}

class CreateMacListWid : public QWidget
{
    Q_OBJECT

public:
    explicit CreateMacListWid(QWidget *parent = nullptr);
    ~CreateMacListWid();

    void refreshWid() {setWid(mUnit);}

protected:
    bool inputCheck();
    void setWid(sMacUnit *unit);
    void saveLog();
    void revokeLog();

private slots:
    void on_typeBox_currentIndexChanged(int index);
    void on_createBtn_clicked();
    void on_revokeBtn_clicked();
    void on_exportBtn_clicked();

private:
    Ui::CreateMacListWid *ui;
    MacsTableWid *mTableWid;
    QList<sMacUnit> mList;
    sMacUnit *mUnit;
};

#endif // CREATEMACLISTWID_H
