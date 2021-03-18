#ifndef CREATEMACWID_H
#define CREATEMACWID_H

#include <QWidget>
#include "macaddr.h"
#include "dbmacs.h"

namespace Ui {
class CreateMacWid;
}

class CreateMacWid : public QWidget
{
    Q_OBJECT

public:
    explicit CreateMacWid(QWidget *parent = nullptr);
    ~CreateMacWid();

    void refreshWid() {setWid(mUnit);}

protected:
    bool inputCheck();
    void setWid(sMacUnit *unit);
    void saveLog(sMacUnit *unit);

private slots:
    void on_typeBox_currentIndexChanged(int index);
    void on_copyBtn_clicked();
    void on_createBtn_clicked();
    void on_revokeBtn_clicked();

private:
    Ui::CreateMacWid *ui;
    sMacUnit *mUnit;
};

#endif // CREATEMACWID_H
