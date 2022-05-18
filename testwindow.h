#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QWidget>
#include <resultform.h>
#include <C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h>
#include <QFileDialog>
#include <chip_param.h>

namespace Ui {
class TestWindow;
}

class TestWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();
    void setParam(ViSession Amper_1, ViSession Source_1, ViSession Two_1, chip_param param_1)
    {
        Amper = Amper_1;
        Source = Source_1;
        Two = Two_1;
        params = param_1;

    };
    void setport(QString port_1)
    {
        port_name = port_1;
    }
signals:
    void firstWindow();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::TestWindow *ui;
    ResultForm *ResWin;
    ViSession Amper,Source,Two;
    QString port_name;
    chip_param params;
};

#endif // TESTWINDOW_H
