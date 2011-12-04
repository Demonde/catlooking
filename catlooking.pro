QT       += core gui network

TARGET = catlooking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        singleapplication.cpp\
        utils.cpp\
    appcontrol.cpp \
    appmodel.cpp

HEADERS  += mainwindow.h\
        singleapplication.h\
        utils.h\
    appcontrol.h \
    appmodel.h

debug {
    DEFINES += DEBUG
}




