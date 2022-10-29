TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        closeview.cpp \
        endview.cpp \
        gamemodel.cpp \
    gameresultmodel.cpp \
    gamesavemodel.cpp \
        gameview.cpp \
        main.cpp \
    menuview.cpp \
    pausemenuview.cpp \
    storyview.cpp

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
    gameresultmodel.hpp \
    gamesavemodel.hpp \
    gameview.hpp \
    menuview.hpp \
    pausemenuview.hpp \
    storyview.hpp \
    sprs/sboard.spr \
    sprs/menu.spr \
    sprs/pause_menu.spr \
    sprs/end.spr \
    sprs/stats.spr \

DISTFILES += \
    README.MD
