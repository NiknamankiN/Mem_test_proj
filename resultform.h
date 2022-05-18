#ifndef RESULTFORM_H
#define RESULTFORM_H

#include <QWidget>
#include <C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h>
#include <QSerialPort>
#include <QtXml>
#include <QPainter>
#include <chip_param.h>

namespace Ui {
class ResultForm;
}

class ResultForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResultForm(QWidget *parent = nullptr);
    ~ResultForm();
    void setParam(ViSession Amper_1, ViSession Source_1, ViSession Two_1, QString Path_1,  char *tests_1, QString port_1, chip_param param_1)
    {
        Amper = Amper_1;
        Source = Source_1;
        Two = Two_1;
        path = Path_1;
        tests[0] = tests_1[0];
        tests[1] = tests_1[1];
        port_name = port_1;
        params = param_1;
    };
signals:
    void firstWindow();
protected:
    void showEvent(QShowEvent *ev);
private slots:

    void on_pushButton_2_clicked();

private:
    Ui::ResultForm *ui;
    ViSession Amper,Source,Two;
    QString path, port_name;
    char tests[2];
    chip_param params;
};

#endif // RESULTFORM_H
