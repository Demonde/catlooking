QT       += core gui network

TARGET = catlooking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        singleapplication.cpp\
        utils.cpp\
    appcontrol.cpp

HEADERS  += mainwindow.h\
        singleapplication.h\
        utils.h\
    appcontrol.h

debug {
    DEFINES += DEBUG
}


