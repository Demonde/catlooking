QT       += core gui network xml

TARGET = catlooking
TEMPLATE = app
win32:DESTDIR = build/windows

SOURCES += \
    main.cpp\
    mainwindow.cpp\
    singleapplication.cpp\
    appcontrol.cpp \
    appmodel.cpp \
    inactivetimer.cpp \
    managingwidget.cpp \
    translator.cpp \
    noteeditwidget.cpp

HEADERS  += \
    mainwindow.h\
    singleapplication.h\
    appcontrol.h \
    appmodel.h \
    inactivetimer.h \
    managingwidget.h \
    translator.h \
    noteeditwidget.h

debug {
    DEFINES += DEBUG
}

RESOURCES += \
    stylesheet.qrc \
    translations.qrc

OTHER_FILES += \
    resources/qss/mainwindow.qss
