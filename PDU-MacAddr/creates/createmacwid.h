#ifndef CREATEMACWID_H
#define CREATEMACWID_H

#include <QWidget>
#include "macaddr.h"
#include "dbmacs.h"
#include "tcpclientsocket.h"

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
    void initWid();
    bool inputCheck();
    bool writeCore();

    bool connect();
    bool readDevType();
    bool writeMac();

    void sleep(int msec);
    void updateResult(int step);
    bool insertText(const QString &status, bool pass=true);
    void setTextColor(bool pass);
    void setWid(sMacUnit *unit);
    void saveLog(sMacUnit *unit);

private slots:
    void on_copyBtn_clicked();
    void on_createBtn_clicked();
    void on_revokeBtn_clicked();
    void on_snCheckBox_clicked(bool checked);
    void on_typeBox_currentIndexChanged(int index);

private:
    Ui::CreateMacWid *ui;
    TcpClientSocket *mSocket;
    sMacUnit *mUnit;
    QString mDevType;
    int mId;
};

#endif // CREATEMACWID_H
