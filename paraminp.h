#ifndef PARAMINP_H
#define PARAMINP_H

#include <QWidget>
#include <testwindow.h>
#include <qpixmap.h>
#include <QSerialPort>
#include <QMessageBox>
#include <C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h>
#include <QSerialPortInfo>
#include <chip_param.h>

namespace Ui {
class ParamInp;
}

class ParamInp : public QWidget
{
    Q_OBJECT

public:
    explicit ParamInp(QWidget *parent = nullptr);
    void setParam(ViSession Amper_1, ViSession Source_1, ViSession Two_1)
    {
        Amper = Amper_1;
        Source = Source_1;
        Two = Two_1;
    };
    ~ParamInp();
signals:
    void firstWindow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::ParamInp *ui;
    TestWindow *SWin;
    ViSession Amper,Source,Two;
    chip_param params;
};

#endif // PARAMINP_H
