QT       += core gui sql
QT       += core gui sql network multimedia multimediawidgets charts printsupport widgets axcontainer serialport
//LIBS += qaxcontainer.lib
QT+=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT+=printsupport
QT+=network

QT       += core gui sql network multimedia charts serialport

QT       += core gui sql multimedia multimediawidgets charts
QT +=charts

CONFIG += c++11
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    avion.cpp \
    billet.cpp \
    connexion.cpp \
    employee.cpp \
    exportexcelobject.cpp \
    gest_arduino.cpp \
    gest_avion.cpp \
    gest_billet.cpp \
    gest_emp.cpp \
    gest_vol.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mydialog.cpp \
    problem.cpp \
    qrcodegen.cpp \
    smtp.cpp \
    stats.cpp \
    vol.cpp

HEADERS += \
    arduino.h \
    arduino.h \
    avion.h \
    billet.h \
    connexion.h \
    employee.h \
    excel.h \
    exportexcelobject.h \
    gest_arduino.h \
    gest_avion.h \
    gest_billet.h \
    gest_emp.h \
    gest_vol.h \
    login.h \
    mainwindow.h \
    mydialog.h \
    problem.h \
    qrcodegen.h \
    smtp.h \
    stats.h \
    vol.h \
    webaxwidget.h

FORMS += \
    gest_arduino.ui \
    gest_avion.ui \
    gest_billet.ui \
    gest_emp.ui \
    gest_vol.ui \
    mainwindow.ui \
    mydialog.ui \
    stats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    airport-terminal.jpg \
    asian-airport.jpg \
    employeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee.jpg \
    lh.jpg \
    plane-passing-by-sun-cloudy-day.jpg \
    qr-code.png \
    qr.png \
    unknown.png

RESOURCES += \
    aaa.qrc
