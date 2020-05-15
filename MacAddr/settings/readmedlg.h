#ifndef READMEDLG_H
#define READMEDLG_H

#include <QDialog>

namespace Ui {
class ReadMeDlg;
}

class ReadMeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ReadMeDlg(QWidget *parent = nullptr);
    ~ReadMeDlg();

protected:
    void initText();

private slots:
    void on_okBtn_clicked();

private:
    Ui::ReadMeDlg *ui;
};

#endif // READMEDLG_H
