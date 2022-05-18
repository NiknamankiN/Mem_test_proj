#include "paraminp.h"
#include "ui_paraminp.h"
#include <iostream>
#include <fstream>

void setpoint(QString *str)
{
    for(int i = 0; i < str->length(); ++i)
        if((*str)[i] == ',')
            (*str)[i] = '.';
}
ParamInp::ParamInp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamInp)
{

    ui->setupUi(this);
    ui->pushButton_3->setDisabled(1);
    ui->pushButton->setDisabled(1);
    ui->pushButton_5->setDisabled(1);
    ui->lineEdit->setReadOnly(1);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//Проверка соединений по COM порту и добавление найденных
    {                                                                       //в выпадающее меню
        ui->comboBox->addItem(info.portName());
        ui->comboBox->setCurrentIndex(0);
        ui->pushButton_3->setEnabled(1);
    }
    SWin = new TestWindow();
    connect(SWin, &TestWindow::firstWindow, this, &ParamInp::show);
}

ParamInp::~ParamInp()
{
    delete ui;
}

void ParamInp::on_pushButton_clicked()//Передача параметров в окно тестирования
{
    SWin->setParam(Amper, Source, Two, params);
    SWin->setWindowTitle("Тестирование");
    this->close();
    SWin->show();
}

void ParamInp::on_pushButton_2_clicked()//Кнопка назад
{
    this->close();
    emit firstWindow();
}

void ParamInp::on_pushButton_3_clicked()//Кнопка проверки соединения с микроконтроллером и микросхемой памяти
{
    QSerialPort serialPort;
    std::cout<<ui->doubleSpinBox;
    QString VCC1 = ui->doubleSpinBox->text(), VCC2 = ui->doubleSpinBox_2->text();
    setpoint(&VCC1);
    setpoint(&VCC2);
    VCC1 = ":APPLy CH1," + VCC1 + ",0";
    VCC1 = ":APPLy CH2," + VCC2 + ",0";
    viWrite(Source, (ViBuf)VCC1.toStdString().c_str(), 512, VI_NULL);
    viWrite(Source, (ViBuf)VCC2.toStdString().c_str(), 512, VI_NULL);
    viWrite(Source, (ViBuf)":OUTPut CH1,ON", 512, VI_NULL);
    viWrite(Source, (ViBuf)":OUTPut CH2,ON", 512, VI_NULL);
    viWrite(Source, (ViBuf)":APPLy CH3,5,0.5", 512, VI_NULL);
    viWrite(Source, (ViBuf)":OUTPut CH3,ON", 512, VI_NULL);

    serialPort.setPortName(ui->comboBox->currentText());
    serialPort.setBaudRate(QSerialPort::Baud19200);
    if (!serialPort.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
        return;
    }
    serialPort.write("L");
    serialPort.waitForBytesWritten();
    QByteArray data;
    while (serialPort.waitForReadyRead(400)) {

        data.append(serialPort.readAll());
        //data = serialPort.readLine();
    }
    if(data.toStdString() == "Mem320")
    {
        SWin->setport(ui->comboBox->currentText());
        ui->pushButton->setEnabled(1);
        QMessageBox::information(this, "Успешно!", "Микросхема памяти и микроконтроллер подключены, можете переходить к тестированию");


    }
    else if(data.toStdString() == "Mem001")
        QMessageBox::information(this, "Внимание!", "Микроконтроллер подключен, для перехода тестирования подключите микросхему памяти");
    else
        QMessageBox::warning(this, "Ошибка", "Микросхема памяти и микроконтроллер не подключены");
    serialPort.close();
}

void ParamInp::on_pushButton_4_clicked()//Обновление доступных COM портов
{
    int curind = ui->comboBox->currentIndex();
    ui->comboBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comboBox->addItem(info.portName());
    }
    if(ui->comboBox->count()>0)
        ui->pushButton_3->setEnabled(1);
    if(ui->comboBox->count()-1>curind)
        ui->comboBox->setCurrentIndex(curind+1);
    else
        ui->comboBox->setCurrentIndex(0);
}

void ParamInp::on_pushButton_5_clicked()//Выбор пути файла с параметрами микросхемы памяти, определёнными в ТУ
{
    QString path = QFileDialog::getOpenFileName(0,QObject::tr("Выберите файл с параметрами тестироуемой микросхемы")
                                                ,QDir::homePath(), QObject::tr("Файл TXT (*.txt)"));
    for(int i = 0; i < path.length(); ++i)
        if(path[i] == '/')
            path[i] = '\\';
    if(path.length() > 0)
        ui->lineEdit->setText(path);
    string st1, st[12];
    std::ifstream myfile;
    myfile.open(path.toStdString(),ios::in);
    if(myfile.is_open())
    {
        for(int i = 0; i < 12; ++i)
        {
            getline(myfile,st1);
            st[i].append(&st1[st1.rfind(':')+1]);
        }

        params.set_all(st[0],stoi(st[1]),stof(st[2]),stof(st[3]),stof(st[4]), stof(st[5]),
                stof(st[6]),stof(st[7]),stof(st[8]),stof(st[9]),stof(st[10]),stof(st[11]));
        myfile.close();


    }
    else
        QMessageBox::warning(this, "Ошибка", "Файл с таким именем не найден!");

}


