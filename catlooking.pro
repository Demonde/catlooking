QT       += core gui network xml

TARGET = catlooking
TEMPLATE = app
DESTDIR         = build
OBJECTS_DIR     = build
MOC_DIR         = build
RCC_DIR         = build
VERSION         = 2.0.0
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
    noteeditwidget.h \
    modelinfo.h \
    notemodelinfo.h

debug {
    DEFINES += DEBUG
}

RESOURCES += \
    stylesheet.qrc \
    translations.qrc

OTHER_FILES += \
    resources/qss/mainwindow.qss \
    resources/qss/daytheme.qss \
    resources/qss/darktheme.qss

# Stuff for Windows
win32 {
    RC_FILE                 = portabase.rc
}
