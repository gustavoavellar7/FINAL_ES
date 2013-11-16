# -------------------------------------------------
# Project created by QtCreator 2009-11-26T21:34:19
# -------------------------------------------------
QT += network
TARGET = chatserver
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    server.cpp \
    connection.cpp
HEADERS += mainwindow.h \
    server.h \
    connection.h
FORMS += mainwindow.ui

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/i386-linux-gnu/release/ -lX11
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/i386-linux-gnu/debug/ -lX11
else:symbian: LIBS += -lX11
else:unix: LIBS += -L$$PWD/../../../../../usr/lib/i386-linux-gnu/ -lX11

INCLUDEPATH += $$PWD/../../../../../usr/lib/i386-linux-gnu
DEPENDPATH += $$PWD/../../../../../usr/lib/i386-linux-gnu
