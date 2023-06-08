QT       += core gui positioning serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++17
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += "DEBUG_=1"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DebugWidget.cpp \
    SetQuadParams.cpp \
    main.cpp \
    mainwindow.cpp \
    serialcontroller.cpp

HEADERS += \
    DebugWidget.h \
    ReceiveCommand.h \
    SendCommand.h \
    SetQuadParams.h \
    mainwindow.h \
    serialcontroller.h

FORMS += \
    DebugWidget.ui \
    SetQuadParams.ui \
    mainwindow.ui \
    serialcontroller.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

