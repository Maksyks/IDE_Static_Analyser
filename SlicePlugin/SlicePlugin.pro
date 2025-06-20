QT       += core
QT       += widgets
CONFIG   += plugin
TEMPLATE = lib
TARGET   = SlicePlugin

# Пусть к интерфейсу IDE
INCLUDEPATH += $$PWD/../

SOURCES += SlicePlugin.cpp
HEADERS += SlicePlugin.h

# JSON-метаданные
DISTFILES += SlicePlugin.json


win32 {

    # 1) Укажем, куда кладёт плагин сам qmake (подпапка debug)
    CONFIG(debug, debug|release) {
        DESTDIR = $$OUT_PWD/debug
    } else {
        DESTDIR = $$OUT_PWD/release
    }

    # 2) Куда копировать результат — папка plugins IDE
    PLUGINDIR = C:\Diplom_project\Static_analyser_plugins\build\Desktop_Qt_6_8_2_MinGW_64_bit-Debug\debug\plugins

    # 3) Команды после линковки плагина:
    #    - создаём папку, если её нет
    #    - копируем DLL
    #    - копируем JSON
    QMAKE_POST_LINK += \
        if not exist \"$$PLUGINDIR\" mkdir \"$$PLUGINDIR\"\n\
        copy /Y \"$$DESTDIR\\$$TARGET.dll\" \"$$PLUGINDIR\\\" \n\
        copy /Y \"$$PWD\\SlicePlugin.json\" \"$$PLUGINDIR\\\" \n
}

