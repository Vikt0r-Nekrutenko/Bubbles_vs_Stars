TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        closeview.cpp \
        endview.cpp \
        gamemodel.cpp \
        gameview.cpp \
        main.cpp \
    menuview.cpp \
    pausemenuview.cpp

LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf \
               $$PWD/../stf/smv \
               $$PWD/../stf/sdb \

DEPENDPATH += $$PWD/../stf \
              $$PWD/../stf/smv \
              $$PWD/../stf/sdb \

HEADERS += \
    closeview.hpp \
    endview.hpp \
    gamemodel.hpp \
    gameview.hpp \
    menuview.hpp \
    pausemenuview.hpp
