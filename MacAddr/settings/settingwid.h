#ifndef SETTINGWID_H
#define SETTINGWID_H

#include "createmaclistwid.h"

namespace Ui {
class SettingWid;
}

class SettingWid : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWid(QWidget *parent = nullptr);
    ~SettingWid();

    void refreshWid() {setWid(mUnit);}

protected:
    void initWid();
    bool inputCheck();
    void setWid(sMacUnit *unit);
    void saveLog(sMacUnit *unit);
    bool authorityVerification();

private slots:
    void on_typeBox_currentIndexChanged(int index);
    void on_btn_clicked();

    void on_readMeBtn_clicked();

private:
    Ui::SettingWid *ui;
    sMacUnit *mUnit;
};

#endif // SETTINGWID_H
