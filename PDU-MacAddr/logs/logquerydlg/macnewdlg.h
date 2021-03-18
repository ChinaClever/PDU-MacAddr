#ifndef NEWUSRDLG_H
#define NEWUSRDLG_H

#include <QDialog>
#include "msgbox.h"
#include "dbmacs.h"
#include "sqltablewid.h"
#include "macaddr.h"

namespace Ui {
class MacNewDlg;
}

class MacNewDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MacNewDlg(QWidget *parent = 0);
    ~MacNewDlg();

    void editTitle(const QString &);
    void loadInfo(sMacItem &it);

    virtual bool saveInfo(sMacItem &it);
protected:
    bool informationCheck(void);

private slots:
    void on_saveBtn_clicked();

private:
    Ui::MacNewDlg *ui;
};

#endif // NEWUSRDLG_H
