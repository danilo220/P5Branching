TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/position.cpp \
    src/route.cpp \
    src/track.cpp \
    src/utilities.cpp \
    src/xmlparser.cpp \
    src/gridworld.cpp \
    src/xmlgenerator.cpp \
    src/all-tests.cpp \
    tests_accepted/N0123456_NonexistantFile.cpp \
    tests_accepted/N0123456_RouteLength.cpp \
    src/n0655279.cpp \
    src/n0655279_maxlon.cpp \
    src/n0655279_maxLon.cpp

HEADERS += \
    headers/gpxp.h \
    headers/position.h \
    headers/route.h \
    headers/track.h \
    headers/utilities.h \
    headers/xmlparser.h \
    headers/gridworld.h \
    headers/xmlgenerator.h

INCLUDEPATH += $$PWD/headers/
INCLUDEPATH += $$PWD/tests_accepted/

LIBS += -lboost_unit_test_framework
