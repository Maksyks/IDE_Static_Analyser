QT       += core gui
QT       += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    CodeEditor.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CodeEditor.h \
    IPluginInterface.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
