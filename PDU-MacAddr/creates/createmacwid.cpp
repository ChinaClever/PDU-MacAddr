/*
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "createmacwid.h"
#include "ui_createmacwid.h"

CreateMacWid::CreateMacWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateMacWid)
{
    ui->setupUi(this);
    initWid();
}

CreateMacWid::~CreateMacWid()
{
    delete ui;
}


void CreateMacWid::initWid()
{
    groupBox_background_icon(this);
    on_typeBox_currentIndexChanged(0);
    ui->revokeBtn->setEnabled(false);
    ui->revokeBtn->setHidden(true);

    mSocket = new TcpClientSocket(this);
    QPalette pl = ui->textEdit->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    ui->textEdit->setPalette(pl);
}

void CreateMacWid::setTextColor(bool pass)
{
    QColor color("black");
    if(!pass) color = QColor("red");
    ui->textEdit->moveCursor(QTextCursor::Start);

    QTextCharFormat fmt;//文本字符格式
    fmt.setForeground(color);// 前景色(即字体色)设为color色
    QTextCursor cursor = ui->textEdit->textCursor();//获取文本光标
    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
    ui->textEdit->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
}


bool CreateMacWid::insertText(const QString &status, bool pass)
{
    setTextColor(pass);
    QString str = QString::number(mId++) + "、"+ status + "\n";
    ui->textEdit->insertPlainText(str);
    if(!pass) CriticalMsgBox box(this, str);

    return pass;
}

void CreateMacWid::setWid(sMacUnit *unit)
{
    ui->macEdit->setText(unit->mac);
    ui->startEdit->setText(unit->start);
    ui->endEdit->setText(unit->end);
    MacAddr::bulid()->macHasCounts(*unit);
    ui->countEdit->setText(QString::number(unit->counts));
}

void CreateMacWid::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool CreateMacWid::connect()
{
    int port = 8765;
    insertText(tr("连接目标设备"));
    mId = 1; ui->textEdit->clear();
    QString ip = ui->ipEdit->text();
    QString str = tr("IP=%1 Port=%2 ").arg(ip).arg(port);
    insertText(tr("连接目标设备"));

    str = tr("连接");
    bool ret = mSocket->connect(ip, port);
    if(ret) str += tr("成功"); else str += tr("错误");
    return insertText(str, ret);
}

bool CreateMacWid::readDevType()
{
    QString str;
    bool ret = false;
    if(ui->typeBox->currentIndex()) {
        ret = true;
        mDevType = ui->typeBox->currentText();
    } else {
        for(int i=0; i<3*10; ++i) {
            QByteArray array = mSocket->read();
            if(array.size() > 3) {
                mDevType = array;
                ret  = true; break;
            } else sleep(100);
        }
    }

    if(ret) str =  tr("目标设备：%1").arg(mDevType);
    else str = tr("无法识别到设备");
    return insertText(str, ret);
}

bool CreateMacWid::writeMac()
{
    QString mac = mUnit->mac;
    QString str = tr("Mac:%1").arg(mac);
    bool ret = mSocket->write(mac.toLocal8Bit());
    insertText(str, ret);

    ret = false;
    for(int i=0; i<3*10; ++i) {
        QByteArray array = mSocket->read();
        if(array.size() > 1) {
            ret  = true; break;
        } else sleep(100);
    }

    str = tr("Mac写入");
    if(ret) str += tr("成功"); else str += tr("错误");
    return insertText(str, ret);
}

bool CreateMacWid::writeCore()
{
    bool ret = connect();
    if(ret) ret = readDevType();
    if(ret) {
        ret = MacAddr::bulid()->createMac(*mUnit);
        if(ret) {
            ret = writeMac();
            mSocket->disConnect();
        } else insertText(tr("Mac创建失败"), ret);
    }

    return ret;
}


void CreateMacWid::on_typeBox_currentIndexChanged(int index)
{
    sMacUnit *unit = sDataPacket::bulid()->mac;
    unit->name = ui->typeBox->currentText();
    ui->revokeBtn->setEnabled(false);
    setWid(unit); mUnit = unit;
    unit->id = index;
}

void CreateMacWid::on_copyBtn_clicked()
{
    QString str = ui->macEdit->text();
    if(!str.isEmpty()) {
        cm_ClipBoardSet(str);
        //InfoMsgBox box(this,tr("MAC地址：%1，已复制!").arg(str));
    }
}

bool CreateMacWid::inputCheck()
{
    QString str = ui->nameEdit->text();
    if(str.isEmpty()) {
        CriticalMsgBox box(this, tr("客户名称不能为空，请重新输入！\n"));
        return false;
    }

    str = ui->ipEdit->text();
    if(!cm_isIPaddress(str)) {
        CriticalMsgBox box(this, tr("设备IP地址输入错误，请重新输入！\n"));
        return false;
    }
    updateResult(0);

    return true;
}

void CreateMacWid::saveLog(sMacUnit *unit)
{
    sMacItem item;
    item.dev = mDevType;
    item.user = ui->nameEdit->text();
    item.sn = ui->snEdit->text();
    item.mac = unit->mac;
    DbMacs::bulid()->insertItem(item);
    ConfigBase::bulid()->setMacUnit(unit);
}


void CreateMacWid::updateResult(int step)
{
    QString style;
    switch (step) {
    case 0: style = "background-color:yellow; color:rgb(0, 0, 0);"; break;
    case 1: style = "background-color:green; color:rgb(255, 255, 255);"; break;
    case 2: style = "background-color:red; color:rgb(255, 255, 255);"; break;
    }

    style += "font:100 36pt \"微软雅黑\";";
    ui->createBtn->setStyleSheet(style);
    if(step == 2) ui->copyBtn->setText(tr("失败"));
}

void CreateMacWid::on_createBtn_clicked()
{
    if(!inputCheck()) return;
    bool ret = writeCore();
    if(ret) {
        setWid(mUnit);
        saveLog(mUnit);
        updateResult(1);
        on_copyBtn_clicked();
        ui->revokeBtn->setEnabled(true);
    } else {
        updateResult(2);
    }
}

void CreateMacWid::on_revokeBtn_clicked()
{
    QuMsgBox box(this, tr("请确认是否撤销？"));
    if(box.Exec()) {
        QString mac = mUnit->mac;
        bool ret = MacAddr::bulid()->revokeMac(*mUnit);
        if(ret) {
            setWid(mUnit);
            DbMacs::bulid()->removeMac(mac);
            ui->revokeBtn->setEnabled(false);
            ConfigBase::bulid()->setMacUnit(mUnit);
        }
    }
}

void CreateMacWid::on_snCheckBox_clicked(bool checked)
{
    ui->snEdit->setEnabled(checked);
}
