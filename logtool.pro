QT       += core
QT       += serialport

QT       -= gui

TARGET = logtool
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
DEFINES += "UseLua=OFF"

SOURCES += main.cpp \
    app/rs232reader.cpp \
    app/logtool.cpp \
    app/logcat.cpp \
    app/blacklistmanager.cpp \
    utils/filereader.cpp \
    utils/flog.cpp \
    utils/filewatcher.cpp \
    utils/linuxfilewatcher.cpp \
    utils/outputprinter.cpp

HEADERS += \
    app/rs232reader.h \
    app/logtool.h \
    app/logcat.h \
    app/blacklistmanager.h \
    utils/filereader.h \
    utils/flog.h \
    utils/filewatcher.h \
    utils/linuxfilewatcher.h \
    utils/outputprinter.h
