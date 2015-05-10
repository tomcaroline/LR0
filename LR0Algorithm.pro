#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T21:37:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LR0Algorithm
TEMPLATE = app

RC_FILE = LR0Algorithm.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    grammar.cpp \
    analyproc.cpp \
    painttree.cpp \
    treenode.cpp \
    painttree_one.cpp \
    introdlg.cpp \
    weima.cpp \
    steptable.cpp \
    steptable_one.cpp \
    alldlg.cpp \
    onedlg.cpp

HEADERS  += mainwindow.h \
    grammar.h \
    analyproc.h \
    painttree.h \
    treenode.h \
    painttree_one.h \
    introdlg.h \
    weima.h \
    steptable.h \
    steptable_one.h \
    alldlg.h \
    onedlg.h

FORMS    += mainwindow.ui

RESOURCES += \
    application.qrc

OTHER_FILES += \
    README.txt \
    LR0Algorithm.rc
