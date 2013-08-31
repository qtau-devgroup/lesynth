TEMPLATE      = lib
CONFIG       += plugin
TARGET        = $$qtLibraryTarget(lesynth)

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

#--------------------------------------------
CONFIG(debug, debug|release) {
    COMPILEDIR = $${OUT_PWD}/debug
} else {
    COMPILEDIR = $${OUT_PWD}/release
}

DESTDIR         = $${COMPILEDIR}/plugins
OBJECTS_DIR     = $${COMPILEDIR}/lesynth/.obj
MOC_DIR         = $${COMPILEDIR}/lesynth/.moc
RCC_DIR         = $${COMPILEDIR}/lesynth/.rcc
UI_DIR          = $${COMPILEDIR}/lesynth/.ui
#--------------------------------------------
