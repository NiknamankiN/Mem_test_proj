#include "testwindow.h"
#include "ui_testwindow.h"
#include <QButtonGroup>
#include <iostream>

TestWindow::TestWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(1);
    ui->lineEdit->setText("D:\\TestResult.xml");
    ResWin = new ResultForm;
    connect(ResWin, &ResultForm::firstWindow, this, &TestWindow::show);
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::on_pushButton_2_clicked() //Кнопка назад
{
    this->close();
    emit firstWindow();

}

void TestWindow::on_pushButton_clicked() //Начало тестирования и передача параметров микросхемы памяти в окно рез-тов
{
    QButtonGroup group,group2;
    QList<QRadioButton *> allButtons = ui->groupBox->findChildren<QRadioButton *>();
    QList<QRadioButton *> allButtons_2 = ui->groupBox_2->findChildren<QRadioButton *>();
    for(int i = 0; i < allButtons.size(); ++i)
    {
        group.addButton(allButtons[i],i);
    }
    for(int i = 0; i < allButtons_2.size(); ++i)
    {
        group2.addButton(allButtons_2[i],i);
    }
    char tests[2];
    tests[0] = group.checkedId()+'0';
    tests[1] = group2.checkedId()+'0';
    ResWin->setWindowTitle("Результаты тестирования");
    ResWin->setParam(Amper, Source, Two, ui->lineEdit->text(), tests, port_name, params);
    this->close();
    ResWin->show();
}

void TestWindow::on_pushButton_4_clicked() //Кнопка "Обзор" для указания пути файла с итогами тестирования
{
    QString path = QFileDialog::getSaveFileName(0,QObject::tr("Укажите файл для сохранения результатов тестирования")
                                                ,QDir::homePath(), QObject::tr("Файл XML (*.xml)"));
    if(path.length() > 0)
        ui->lineEdit->setText(path);

}
