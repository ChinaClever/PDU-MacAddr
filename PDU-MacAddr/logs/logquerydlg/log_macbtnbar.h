#ifndef USERBTNBAR_H
#define USERBTNBAR_H

#include "maceditdlg.h"
#include "logcomwid.h"

class Log_MacBtnBar : public LogBtnBar
{
    Q_OBJECT
public:
    explicit Log_MacBtnBar(QWidget *parent = nullptr);

signals:

protected :
     void addBtn();
     void modifyBtn(int id);
};

#endif // USERBTNBAR_H
