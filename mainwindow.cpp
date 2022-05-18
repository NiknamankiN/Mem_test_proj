#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <C:\Program Files\IVI Foundation\VISA\Win64\Include\visa.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "windows.h"
#include <QSerialPort>
#include <QMessageBox>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SWin = new ParamInp();
    SWin->setWindowTitle("Ввод параметров микросхемы");

    connect(SWin, &ParamInp::firstWindow, this, &MainWindow::show);
    ui->pushButton_3->setDisabled(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()//Проверка подключения мультиметра и источника питания
{
    strcpy(Source_name, "DP832A");
    strcpy(Amper_name, "DM3068");
    ViSession rmSession, scopeSession = 0, amSession = 0, tempSess = 0;
    ViFindList resourceList;
    ViUInt32 numResources;
    std::string mess[4];
    mess[0] = "Приборы не обнаружены!\nПроверьте подключение ";
    mess[1] = "амперметра";
    mess[2] = " и ";
    mess[3] = "источника питания";
    int i = 0;
    char readStr[512];
    char usbResource[VI_FIND_BUFLEN];

    viOpenDefaultRM(&rmSession);
    viFindRsrc(rmSession, "USB?*INSTR", &resourceList, &numResources, usbResource);
    if(int(numResources) > 0)
    {
        viOpen(rmSession, usbResource, VI_NULL, VI_NULL, &tempSess);
        viWrite(tempSess, (ViBuf)"*IDN?", 512, VI_NULL);
        viRead(tempSess, (ViBuf)readStr, 512, VI_NULL);
        for(i = 0; i < int(numResources);)
        {
            std::cout<<readStr<<"\n";
            if(strstr(readStr,Source_name))
            {
                scopeSession = tempSess;
                ++i;
                mess[2].clear();
                mess[3].clear();
                if(i < int(numResources))
                {
                    viFindNext(resourceList,usbResource);
                    viOpen(rmSession, usbResource, VI_NULL, VI_NULL, &tempSess);
                    memset(readStr,0,512);
                    viWrite(tempSess, (ViBuf)"*IDN?", 512, VI_NULL);
                    viRead(tempSess, (ViBuf)readStr, 512, VI_NULL);
                }

            }
            if(strstr(readStr,Amper_name))
            {
                amSession = tempSess;
                ++i;
                mess[1].clear();
                mess[2].clear();
                if(i < int(numResources))
                {
                    viFindNext(resourceList,usbResource);
                    viOpen(rmSession, usbResource, VI_NULL, VI_NULL, &tempSess);
                    memset(readStr,0,512);
                    viWrite(tempSess, (ViBuf)"*IDN?", 512, VI_NULL);
                    viRead(tempSess, (ViBuf)readStr, 512, VI_NULL);
                }
            }
        }
    }
    if(i == 2)
    {
        ui->pushButton->setDisabled(1);
        ui->pushButton_3->setEnabled(1);
        QMessageBox::information(this,"Успешно","Амперметр и источник питания подключены!");
        SWin->setParam(amSession, scopeSession, rmSession);
    }
    else
    {
        QMessageBox::warning(this,"Ошибка", QString::fromStdString(mess[0] + mess[1] + mess[2] + mess[3] + " и попробуйте снова!"));
        ui->pushButton->setDisabled(1);
        ui->pushButton_3->setEnabled(1);
        QMessageBox::information(this,"Успешно","Амперметр и источник питания подключены!");
        SWin->setParam(amSession, scopeSession, rmSession);
    }
    memset(readStr,0,512);
    viWrite(scopeSession, (ViBuf)":APPLy CH1,5,0", 512, VI_NULL);
    //viWrite(scopeSession, (ViBuf)":OUTPut CH1,ON", 512, VI_NULL);
    viRead(amSession, (ViBuf)readStr, 512, VI_NULL);
    //std::cout<<"Source voltage: " <<readStr <<"\n";

    memset(readStr,0,512);
    //viWrite(amSession, (ViBuf)":MEASure:VOLTage:DC MIN", 512, VI_NULL);
    viWrite(amSession, (ViBuf)":MEASure:VOLTage:DC?", 512, VI_NULL);
    viRead(amSession, (ViBuf)readStr, 512, VI_NULL);

}



void MainWindow::on_pushButton_3_clicked()//Кнопка далее
{
    SWin->show();
    this->close();

}

void MainWindow::on_pushButton_4_clicked()//Кнопка выхода
{
    this->close();
}
