QT       += core gui network

TARGET = catlooking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        singleapplication.cpp\
        utils.cpp\

HEADERS  += mainwindow.h\
        singleapplication.h\
        utils.h\

debug {
    DEFINES += DEBUG
}
