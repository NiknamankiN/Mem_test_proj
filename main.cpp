#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Стартовое меню");
    w.show();
    return a.exec();
}
