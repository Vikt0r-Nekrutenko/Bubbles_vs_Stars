TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    model/sources/gamemodel.cpp \
    model/sources/gameresultmodel.cpp \
    model/sources/gamesavemodel.cpp \
    views/sources/closeview.cpp \
    views/sources/endview.cpp \
    views/sources/gameview.cpp \
    views/sources/menuview.cpp \
    views/sources/pausemenuview.cpp \
    views/sources/storyview.cpp

LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf \
               $$PWD/../stf/smv \
               $$PWD/../stf/sdb \
               $$PWD/model/headers \
               $$PWD/views/headers \

DEPENDPATH += $$PWD/../stf \
              $$PWD/../stf/smv \
              $$PWD/../stf/sdb \
              $$PWD/model/headers \
              $$PWD/views/headers \

HEADERS += \
    model/headers/gamemodel.hpp \
    model/headers/gameresultmodel.hpp \
    model/headers/gamesavemodel.hpp \
    views/headers/closeview.hpp \
    views/headers/endview.hpp \
    views/headers/gameview.hpp \
    views/headers/menuview.hpp \
    views/headers/pausemenuview.hpp \
    views/headers/storyview.hpp

DISTFILES += \
    README.MD \
    sprs/sboard.spr \
    sprs/menu.spr \
    sprs/pause_menu.spr \
    sprs/end.spr \
    sprs/stats.spr \
