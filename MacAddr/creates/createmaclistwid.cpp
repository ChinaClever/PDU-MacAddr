#include "createmaclistwid.h"
#include "ui_createmaclistwid.h"
#include "sqlexportdlg.h"

CreateMacListWid::CreateMacListWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateMacListWid)
{
    ui->setupUi(this);
    groupBox_background_icon(this);
    on_typeBox_currentIndexChanged(0);
    ui->revokeBtn->setEnabled(false);
    mTableWid = new MacsTableWid(ui->widget);
}

CreateMacListWid::~CreateMacListWid()
{
    delete ui;
}

void CreateMacListWid::setWid(sMacUnit *unit)
{
    ui->startEdit->setText(unit->start);
    ui->endEdit->setText(unit->end);
    MacAddr::bulid()->macHasCounts(*unit);
    ui->countEdit->setText(QString::number(unit->counts));
}

void CreateMacListWid::on_typeBox_currentIndexChanged(int index)
{
    sMacUnit *unit = nullptr;
    sMacAddrs *macs = sDataPacket::bulid()->macs;
    switch (index) {
    case 0:  unit = &(macs->IP); break;
    case 1:  unit = &(macs->MPDU); break;
    case 2:  unit = &(macs->RPDU); break;
    case 3:  unit = &(macs->ZPDU); break;
    case 4:  unit = &(macs->ATS); break;
    }
    mUnit = unit;
    setWid(unit);
    mList.clear();
    ui->revokeBtn->setEnabled(false);
}

bool CreateMacListWid::inputCheck()
{
    QString str = ui->nameEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("客户名称不能为空，请重新输入！\n"));
        return false;
    }

    QuMsgBox box(this, tr("请确认是否批量生成？"));
    return box.Exec();
}

void CreateMacListWid::saveLogSlot()
{
    sMacItem item;
    ConfigBase::bulid()->setMacUnit(mUnit);
    item.dev = ui->typeBox->currentText();
    item.user = ui->nameEdit->text();

    Db_Tran db;
    for(int i=0; i<mList.size(); ++i) {
        item.sn = QString::number(i+1);
        item.mac = mList.at(i).mac;
        DbMacs::bulid()->insertItem(item);
    }
}

void CreateMacListWid::revokeLogSlot()
{
    Db_Tran db;
    for(int i=0; i<mList.size(); ++i) {
        QString mac = mList.at(i).mac;
        DbMacs::bulid()->removeMac(mac);
    }

    mList.clear();
    ConfigBase::bulid()->setMacUnit(mUnit);
}


void CreateMacListWid::on_createBtn_clicked()
{
    if(!inputCheck()) return;
    int num = ui->spinBox->value();
    mList = MacAddr::bulid()->createMacList(*mUnit, num);
    if(mList.size()) {
        setWid(mUnit);
        mTableWid->setData(mList);
        ui->revokeBtn->setEnabled(true);
        QTimer::singleShot(rand()%200,this,SLOT(saveLogSlot()));
        InfoMsgBox box(this, tr("MAC地址已生成！"));
    } else {
        CriticalMsgBox box(this, tr("创建失败"));
    }
}

void CreateMacListWid::on_revokeBtn_clicked()
{
    QuMsgBox box(this, tr("请确认是否撤销？"));
    if(box.Exec()) {
        bool ret = MacAddr::bulid()->revokeMacList(*mUnit, mList);
        if(ret) {
            setWid(mUnit);
            mTableWid->clearRows();
            ui->revokeBtn->setEnabled(false);
            QTimer::singleShot(rand()%150,this,SLOT(revokeLog()));
            InfoMsgBox box(this, tr("MAC地址已撤销！"));
        }
    }
}

void CreateMacListWid::on_exportBtn_clicked()
{
    if(mList.size()) {
        SqlExportDlg dlg(this);
        QList<QStringList> list; // 内容
        for(int i=0; i<mList.size(); ++i) {
            QStringList strs;
            strs << QString::number(i+1) << mList.at(i).mac;
            list << strs;
        }

        QString str = ui->nameEdit->text();
        QString fn = str + "_" + ui->typeBox->currentText();
        dlg.init(fn, list);
        dlg.exec();

    } else {
        CriticalMsgBox box(this, tr("没有数据无法导出！\n"));
    }
}
