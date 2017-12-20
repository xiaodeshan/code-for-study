#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T09:54:50
#
#-------------------------------------------------

QT       += core gui
RC_ICONS += app.ico

QMAKE_LFLAGS=-static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = memory
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    modeparent.cpp \
    memorymain.cpp \
    learnscopedialog.cpp \
    trainmode.cpp \
    trainwin.cpp \
    timerlabel.cpp \
    statewin.cpp \
    showwin.cpp \
    studymode.cpp \
    learnscopeentity.cpp \
    checkmode.cpp \
    unfamilarmode.cpp


HEADERS += \
    memorymain.h \
    learnscopedialog.h \
    trainwin.h \
    timerlabel.h \
    statewin.h \
    showwin.h \
    global.h \
    modeparent.h \
    studymode.h \
    modeparent.h \
    statewin.h \
    learnscopeentity.h \
    checkmode.h \
    trainmode.h \
    unfamilarmode.h

FORMS += \
    learnscopedialog.ui

DISTFILES += \
    README.md \
    bugs.txt


