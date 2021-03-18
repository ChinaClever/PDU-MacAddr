#ifndef EDITUSRDLG_H
#define EDITUSRDLG_H
#include "macnewdlg.h"

class MacEditDlg : public MacNewDlg
{
    Q_OBJECT

public:
    MacEditDlg(QWidget *parent = 0);
    ~MacEditDlg();

    void setId(int id);

protected:
     bool saveInfo(sMacItem &it);

private:
     int mId;
};

#endif // EDITUSRDLG_H
