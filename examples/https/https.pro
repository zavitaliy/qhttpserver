TARGET = httpshelloworld

QT += network
QT -= gui

CONFIG += debug

INCLUDEPATH += ../../src
LIBS += -L../../lib

win32 {
    debug: LIBS += -lqhttpserverd
    else: LIBS += -lqhttpserver
} else {
    LIBS += -lqhttpserver
}

SOURCES = https.cpp
HEADERS = https.h

RESOURCES += \
    cert.qrc
