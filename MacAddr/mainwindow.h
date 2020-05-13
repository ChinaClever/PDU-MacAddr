#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "navbarwid.h"
#include "settingwid.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void initWid();

protected slots:
    void initFunSlot();
    void navBarSlot(int);


private:
    Ui::MainWindow *ui;
    SettingWid *mSet;
    NavBarWid *mNavBarWid;
    CreateMacWid *mCreateMacWid;
    CreateMacListWid *mMacListWid;
};
#endif // MAINWINDOW_H
