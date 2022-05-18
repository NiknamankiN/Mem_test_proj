QT       += core gui serialport xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    paraminp.cpp \
    resultform.cpp \
    testwindow.cpp

HEADERS += \
    chip_param.h \
    mainwindow.h \
    paraminp.h \
    resultform.h \
    testwindow.h

FORMS += \
    mainwindow.ui \
    paraminp.ui \
    resultform.ui \
    testwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc/' -lvisa32

INCLUDEPATH += 'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc'
DEPENDPATH += 'C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc'

RESOURCES += \
    Res.qrc
