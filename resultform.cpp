#include "resultform.h"
#include "ui_resultform.h"
#include <QMessageBox>


QString ret_err_name(char err) //Полное название неисправности памяти по кодовому символу
{
    switch (err) {
    case 'S':
        return "SAF";
    case 'O':
        return "OED";
    case 'R':
        return "RD";
    case 'T':
        return "TF";
    case 'W':
        return "WPD/BPD";
    case 'D':
        return "WED/BED";
    }
    return 0;
}
QString ret_test_name(char test) //Полное название функционального теста по его Id
{
    switch (test) {
    case '0':
        return "Тест 1";
        break;
    case '1':
        return "Тест 2";
        break;
    case '2':
        return "Тест 3";
        break;
    case '3':
        return "Flash-March";
        break;
    case '4':
        return "March-FT";
        break;
    case '5':
        return "Нет";
        break;
    }
    return 0;
}


ResultForm::ResultForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultForm)
{
    ui->setupUi(this);

}

ResultForm::~ResultForm()
{
    delete ui;
}


void ResultForm::showEvent(QShowEvent *ev)//Передача параметров тестирования микроконтроллеру, получение рез-тов и их отображение
{                                         //Данные передаются по UART

    QSerialPort serialPort;
    bool flag = 1;
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    serialPort.setPortName(port_name);
    serialPort.setBaudRate(QSerialPort::Baud19200);
    serialPort.open(QIODevice::ReadWrite);
    QByteArray data;
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Memory_name");
    xmlWriter.writeCharacters(QString::fromStdString(params.name));
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("Functional_testing");
    QString test_name = ret_test_name(tests[0]);
    xmlWriter.writeAttribute("name",test_name);
    test_name = QString::number(params.size) + " bytes";
    xmlWriter.writeAttribute("memory_size", test_name);

    QByteArray q_b(tests,2);
    serialPort.write(q_b);
    serialPort.waitForBytesWritten();
    QHash<int, int> hash;
    while(data.toStdString() != "F")
    {
        while (serialPort.waitForReadyRead(50)) {
            data = serialPort.readAll();
        }
        if(data.size()>0 && data.toStdString() != "F")
        {
            int two_p[3];
            memcpy(&two_p, q_b.data(), 3);
            int place = (two_p[0]*110 +two_p[1])*8 + two_p[2];
            char err = q_b.toStdString()[2];
            if(!hash.contains(two_p[0]*110 +two_p[1]))
                hash.insert(two_p[0]*110 +two_p[1],1);
            QString err_name = ret_err_name(err);
            xmlWriter.writeStartElement(QString::fromStdString(q_b.toStdString()));
            xmlWriter.writeCharacters(QString::number(place));
            xmlWriter.writeEndElement();
            data.clear();
        }
    }
    data.clear();
    QString var1;
    if(hash.size() > 0)
    {
        test_name = "Неисправно " + QString::number(hash.size()) + " байта";
        var1 = "Не годен";
    }
    else
    {
        test_name = "Память полностью исправна";
        var1 = "Годен";
    }
    xmlWriter.writeStartElement("Functional_outcome");
    xmlWriter.writeCharacters(test_name);
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("Functional_result");
    xmlWriter.writeCharacters(var1);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("Param_testing");
    if(tests[1] == '1')
    {
        xmlWriter.writeStartElement("Param_result");
        xmlWriter.writeCharacters("Не проводилось");
        xmlWriter.writeEndElement();
    }
    else
    {
        QString SCL[5] = {"-","-","+","+","+"};
        QString SDA[5] = {"+","+","+","-","+"};
        QString WP[5] = {"-","-","-","+","+"};
        QString meas[5] = {"SCL","WP","SCL","SDA","SDA"};
        QString pers[5] = {QString::number(params.CR_dev[0]),QString::number(params.CR_dev[1]),QString::number(params.CR_dev[2]),
                           QString::number(params.CR_dev[3]),QString::number(params.CR_dev[4])};
        QString CR[5] = {QString::number(params.CR[0]),QString::number(params.CR[1]),QString::number(params.CR[2]),
                         QString::number(params.CR[3]),QString::number(params.CR[4])};
        for(int i = 0; i < 5; ++i)
        {
            xmlWriter.writeStartElement("param");
            xmlWriter.writeAttribute("SCL",SCL[i]);
            xmlWriter.writeAttribute("SDA",SDA[i]);
            xmlWriter.writeAttribute("WP",WP[i]);
            xmlWriter.writeStartElement(meas[i]);
            xmlWriter.writeAttribute("measurement_unit","A");
            while(!data[0])
                while (serialPort.waitForReadyRead(10)) {
                    data.append(serialPort.readAll());
                }
            char readStr[30];
            viWrite(Amper, (ViBuf)":MEASure:CURRent:DC?", 512, VI_NULL);
            memset(readStr, 0, 30);
            xmlWriter.writeCharacters(QString::fromUtf8(readStr));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Standart");
            xmlWriter.writeAttribute("measurement_unit","uA");
            xmlWriter.writeAttribute("standart_variance","+-"+pers[i]+"%");
            xmlWriter.writeCharacters(CR[i]);
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("acceptance");
            if(abs(std::stof(readStr))*1000000 < 10)
                xmlWriter.writeCharacters("Норма");
            else
            {
                flag = 0;
                xmlWriter.writeCharacters("Не норма");
            }
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeStartElement("Param_result");
        if(flag)
            xmlWriter.writeCharacters("Годен");
        else
            xmlWriter.writeCharacters("Не годен");
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("Result");
    if(flag and hash.size() == 0)
        xmlWriter.writeCharacters("Годен");
    else
        xmlWriter.writeCharacters("Не годен");
    xmlWriter.writeEndElement();
    file.close();
    serialPort.close();
}


void ResultForm::on_pushButton_2_clicked() //Кнопка выхода
{
    this->close();
}
