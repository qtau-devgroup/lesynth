TEMPLATE      = lib
CONFIG       += plugin
TARGET        = $$qtLibraryTarget(lesynth)
DESTDIR       = ../../../bin/plugins/

INCLUDEPATH += ../../

HEADERS += \
    leConfig.h \
    leSynth.h \
    ../../tools/utauloid/ust.h \
    ../../tools/utauloid/oto.h

SOURCES += \
    leSynth.cpp \
    ../../tools/utauloid/ust.cpp \
    ../../tools/utauloid/oto.cpp
